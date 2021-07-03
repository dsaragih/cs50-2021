SELECT name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
AND phone_calls.caller = (SELECT phone_number FROM people WHERE name="Ernest");