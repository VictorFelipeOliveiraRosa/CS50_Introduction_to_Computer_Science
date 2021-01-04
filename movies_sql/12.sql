    SELECT title
      FROM movies m
INNER JOIN stars s
        ON m.id = s.movie_id
INNER JOIN people p
        ON s.person_id = p.id
     WHERE (p.name = "Johnny Depp"
        OR p.name = "Helena Bonham Carter")
  GROUP BY m.id
HAVING COUNT(p.id) = 2;