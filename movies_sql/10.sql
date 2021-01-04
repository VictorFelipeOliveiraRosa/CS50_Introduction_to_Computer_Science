    SELECT name
      FROM people p
INNER JOIN directors d
        ON p.id = d.person_id
INNER JOIN movies m
        ON d.movie_id = m.id
INNER JOIN ratings r
        ON m.id = r.movie_id
     WHERE rating >= 9
	 GROUP BY p.id;