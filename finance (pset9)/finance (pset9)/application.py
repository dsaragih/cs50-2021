import os
import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

#db.execute("CREATE TABLE history (user_id INTEGER, timestamp TEXT, symbol TEXT, name TEXT, shares INTEGER, price NUMERIC, type TEXT, FOREIGN KEY(user_id) REFERENCES users(id))")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute(
        "SELECT symbol, name, SUM(shares) FROM history WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])
    balance = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    total = balance

    for row in rows:
        price = lookup(row['symbol'])['price']
        shares = row['SUM(shares)']

        holding = price * shares
        row['price'] = price
        row['holding'] = holding

        total += holding

    return render_template("index.html", rows=rows, balance=balance, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        sym = request.form.get("symbol")

        try:
            n = float(request.form.get("shares"))
        except:
            return apology("Enter a positive integer")

        if not sym:
            return apology("Enter a symbol")
        elif not lookup(sym):
            return apology("Invalid symbol")
        elif n <= 0 or n != int(n):
            return apology("Enter a positive integer")

        db.execute("BEGIN TRANSACTION")
        price = lookup(sym)["price"]
        name = lookup(sym)["name"]
        row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        balance = row[0]["cash"]

        if balance < price:
            return apology("You don't have enough money for the purchase")

        db.execute("INSERT INTO history (user_id, timestamp, symbol, name, shares, price, type) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   session["user_id"], datetime.datetime.now(), sym, name, n, n*price, 'buy')
        db.execute("UPDATE users SET cash = ? WHERE id = ?", balance - n*price, session["user_id"])
        db.execute("COMMIT")
        return redirect("/")
    else:
        return render_template("buy.html")

    return apology("Unable to buy shares")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT timestamp, symbol, name, price, shares, type FROM history WHERE user_id = ?", session['user_id'])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    symbol = request.form.get("symbol")
    if request.method == "POST":
        if not lookup(symbol):
            return apology("ticker symbol not found")
        else:
            return render_template("quotes.html", lookup=lookup(symbol))
    else:
        return render_template("quote.html")

    return apology("Unable to retrive quote")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Enter a username")
        elif db.execute("SELECT * FROM users WHERE username = ?", username):
            return apology("Username already exists.")
        elif not password or not confirmation:
            return apology("Enter your password")
        elif password != confirmation:
            return apology("Your passwords don't match")
        else:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
            return redirect("/login")

        return apology("Unable to register user.")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        sym = request.form.get("symbol")
        n = int(request.form.get("shares"))

        if not sym:
            return apology("Enter a symbol")
        elif not lookup(sym):
            return apology("Invalid symbol")
        elif n <= 0 or not isinstance(n, int):
            return apology("Enter a positive integer")

        db.execute("BEGIN TRANSACTION")
        price = lookup(sym)["price"]
        name = lookup(sym)["name"]
        row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        balance = row[0]["cash"]

        user_history = db.execute(
            "SELECT symbol, SUM(shares) FROM history WHERE user_id = ? AND symbol = ? GROUP BY symbol", session['user_id'] ,sym)

        if not user_history:
            return apology("You don't own shares of that company")
        elif user_history[0]['SUM(shares)'] < n:
            return apology("You're selling more shares than you own")

        db.execute("INSERT INTO history (user_id, timestamp, symbol, name, shares, price, type) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   session["user_id"], datetime.datetime.now(), sym, name, -n, n*price, 'sell')
        db.execute("UPDATE users SET cash = ? WHERE id = ?", balance + n*price, session["user_id"])
        db.execute("COMMIT")

        return redirect("/")
    else:
        user_history = db.execute(
            "SELECT symbol FROM history WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session['user_id'])
        return render_template("sell.html", rows=user_history)

    return apology("Unable to sell shares")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)