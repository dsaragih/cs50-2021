-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Checks the crime scene reports for surface-level details of the case
SELECT description FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28 AND street="Chamberlin Street";

-- Check the relevant interviews
SELECT transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28;

-- Checks the license plates within the time period
SELECT activity, license_plate FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

-- Matches the name of people to the license plates found
SELECT license_plate, name FROM people
WHERE license_plate
IN(SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);

-- Checks for calls between the times and that were less than a minute
SELECT caller, receiver, duration FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;

-- Selects the name of the callers during that time period
SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60);

-- Selects the name of the people who match the calling time and exit time from the parking lot
SELECT name FROM people
JOIN phone_calls ON people.phone_number = caller
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
WHERE phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration < 60 AND
courthouse_security_logs.hour = 10 AND courthouse_security_logs.minute >= 15 AND courthouse_security_logs.minute <= 25;

-- Selects people who received calls during the time period
SELECT name FROM people
WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60);

-- Identifies the airport id at Fiftyville
SELECT id FROM airports WHERE city = "Fiftyville";

-- Shows the flight ids and departure times to find the earliest flight
SELECT id, hour, minute, destination_airport_id FROM flights WHERE origin_airport_id = 8 AND year = 2020 AND month = 7 AND day = 29;

-- Use the flight id retrieved to select the passengers
SELECT passport_number FROM passengers WHERE flight_id = 36;

-- Use the passport numbers to match names
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- Find the destination city for the flight
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = 36);

-- Checks who was the person that withdrew money and match that person to their name
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7
AND atm_transactions.day = 28 AND atm_location="Fifer Street" AND transaction_type="withdraw"

-- Combines license plate, caller, passport, and ATM transaction information to find the thief
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7
AND atm_transactions.day = 28 AND atm_location="Fifer Street" AND transaction_type="withdraw"
AND name IN (SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36))
AND name IN (SELECT name FROM people
JOIN phone_calls ON people.phone_number = caller
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
WHERE phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration < 60 AND
courthouse_security_logs.hour = 10 AND courthouse_security_logs.minute >= 15 AND courthouse_security_logs.minute <= 25);

-- Once the thief is found, search for the receiver of the call where the caller is the thief
SELECT name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
AND phone_calls.caller = (SELECT phone_number FROM people WHERE name="Ernest");