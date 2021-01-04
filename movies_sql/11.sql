    SELECT title
      FROM movies m
INNER JOIN stars s
        ON m.id = s.movie_id
INNER JOIN ratings r
        ON m.id = r.movie_id
INNER JOIN people p
        ON s.person_id = p.id
     WHERE p.name = "Chadwick Boseman"
  ORDER BY r.rating DESC
     LIMIT 5;