      SELECT AVG(s.energy)
        FROM songs s
  INNER JOIN artists a
          ON s.artist_id = a.id
       WHERE a.name = 'Drake';