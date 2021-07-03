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