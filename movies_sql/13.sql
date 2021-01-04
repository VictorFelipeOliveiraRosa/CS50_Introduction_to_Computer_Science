    SELECT name
      FROM people p
INNER JOIN stars s
        ON p.id = s.person_id
     WHERE s.movie_id IN (
            SELECT movie_id
              FROM stars s
        INNER JOIN people p
                ON p.id = s.person_id
             WHERE p.name = "Kevin Bacon"
               AND p.birth = 1958
    )
	AND p.name != "Kevin Bacon"
	GROUP BY p.id;