-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Description of Theft -> I will go interview
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street" LIMIT 1;

-- Interviews
SELECT name, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";
    -- Ruth Interview: Get license plates of cars
    SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit";
    -- Eugene Interview: Get ATM info
    SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
    SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw");
    -- Raymond Interview: Get phone info and first plane destination
    SELECT destination_airport_id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = 8 ORDER BY hour ASC, minute ASC LIMIT 1;
    SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = 8 ORDER BY hour ASC, minute ASC LIMIT 1);
        -- It's destination was to NYC
    SELECT caller, receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
    -- Emma: half hour sus call

-- I need to get a list of suspects using the info I got
    -- Theif Info:
    SELECT name FROM people WHERE
        id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw")) AND
        phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND
        passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = 8 ORDER BY hour ASC, minute ASC LIMIT 1)) AND
        license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit");
    -- Accomplice Info:
    SELECT id, name, phone_number, passport_number, license_plate FROM people WHERE phone_number IN (
        SELECT receiver FROM phone_calls WHERE caller = (
            SELECT phone_number FROM people WHERE id = (
                SELECT id FROM people WHERE id IN (
                    SELECT person_id FROM bank_accounts WHERE account_number IN (
                        SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"))
                AND phone_number IN (
                    SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
                AND passport_number IN (
                    SELECT passport_number FROM passengers WHERE flight_id = (
                        SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = 8 ORDER BY hour ASC, minute ASC LIMIT 1))
                AND license_plate IN (
                    SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit")))
        AND year = 2021
        AND month = 7
        AND day = 28
        AND duration < 60);