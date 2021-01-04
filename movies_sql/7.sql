SELECT title, rating
  FROM movies m
 INNER JOIN ratings r
    ON r.movie_id = m.id
 WHERE m.year = 2010 AND rating IS NOT NULL
 ORDER BY rating DESC, title ASC