SELECT name FROM people
JOIN phone_calls ON people.phone_number = caller
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
WHERE phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration < 60 AND
courthouse_security_logs.hour = 10 AND courthouse_security_logs.minute >= 15 AND courthouse_security_logs.minute <= 25
AND name IN (SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36));