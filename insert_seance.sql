CREATE PROCEDURE `insert_seance` (IN compared_id INT)
BLOCK1: BEGIN
	CREATE TEMPORARY TABLE log
	LIKE seance_log;
    CREATE TEMPORARY TABLE compared_log
	LIKE seance_log;
BLOCK2: BEGIN
	DECLARE done, inner_done BOOLEAN DEFAULT FALSE;
	DECLARE diff BOOL DEFAULT TRUE;
    DECLARE current_id, se_id, q_id, ans INT;
    DECLARE compared CURSOR FOR
		SELECT seance_id, question_id, answer FROM seance_log
        WHERE seance_id = compared_id;
    DECLARE seance CURSOR FOR
        SELECT seance_id FROM seances
        WHERE seance_id <> compared_id;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    
    OPEN compared;
    WHILE NOT done DO
		FETCH compared INTO se_id, q_id, ans;
		INSERT INTO compared_log (seance_id, question_id, answer)
			VALUES (se_id, q_id, ans);
    END WHILE;
    CLOSE compared;
    SET done = FALSE;
    
    OPEN seance;
    WHILE NOT done DO
		FETCH seance INTO current_id;
        DELETE FROM log;
		BLOCK3: BEGIN
			DECLARE answers CURSOR FOR
				SELECT seance_id, question_id, answer FROM seance_log
				WHERE seance_id = current_id;
			DECLARE CONTINUE HANDLER FOR NOT FOUND SET inner_done = TRUE;
            DELETE FROM log;
            OPEN answers;
            WHILE NOT inner_done DO
				FETCH answers INTO se_id, q_id, ans;
                INSERT INTO log (seance_id, question_id, answer)
					VALUES (se_id, q_id, ans);
			END WHILE;
            CLOSE answers;
            SELECT IF ((SELECT COUNT(*) FROM (SELECT 'log' AS `set`, l.*
				FROM log l
				WHERE ROW(l.seance_id, l.question_id, l.answer) NOT IN
				(SELECT * FROM compared_log)
				UNION ALL
				SELECT 'compared_log' AS `set`, cl.*
				FROM compared_log cl
				WHERE ROW(cl.seance_id, cl.question_id, cl.answer) NOT IN
				(SELECT * FROM log)
                ) AS matches),FALSE,TRUE) INTO diff;
			CASE WHEN diff = FALSE
				THEN DELETE FROM seance_log
					WHERE seance_id = compared_id;
                UPDATE seances SET count = count + 1
					WHERE seance_id = compared_id;
			END CASE;
			SET done = NOT diff;
		END BLOCK3;
    END WHILE;
    CLOSE seance;
END BLOCK2;
END BLOCK1
