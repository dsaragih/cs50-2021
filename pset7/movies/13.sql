SELECT name FROM people
JOIN stars on people.id = stars.person_id
WHERE stars.movie_id IN (
SELECT movies.id FROM movies
JOIN stars on movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = "Kevin Bacon"
) AND name IS NOT "Kevin Bacon";