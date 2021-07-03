-- WITH Helena AS(
-- SELECT * FROM stars
-- WHERE person_id in
-- (SELECT id FROM people WHERE name = "Helena Bonham Carter")
-- )
-- SELECT title FROM movies
-- WHERE id IN (SELECT stars.movie_id
-- FROM stars
-- JOIN Helena
-- ON stars.movie_id = Helena.movie_id
-- WHERE stars.person_id in
-- (SELECT id FROM people WHERE name = "Johnny Depp"));

WITH Helena AS (
SELECT movie_id FROM stars
WHERE person_id = (SELECT id FROM people WHERE name = "Helena Bonham Carter")
)
SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN Helena ON movies.id = Helena.movie_id
WHERE stars.person_id = (SELECT id FROM people WHERE name = "Johnny Depp");