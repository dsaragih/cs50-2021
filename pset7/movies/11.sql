SELECT title FROM movies
JOIN ratings on movies.id = ratings.movie_id
JOIN stars on movies.id = stars.movie_id
WHERE stars.person_id = (SELECT id FROM people WHERE name = "Chadwick Boseman")
ORDER BY rating DESC
LIMIT 5;