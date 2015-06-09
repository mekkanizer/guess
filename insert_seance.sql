CREATE PROCEDURE `insert_seance` (IN compared_id INT)
BLOCK1: BEGIN
	CREATE TEMPORARY TABLE log
	LIKE seance_log;
    CREATE TEMPORARY TABLE compared_log
	LIKE seance_log;
BLOCK2: BEGIN
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
    -- not really sure if true
    SET done = TRUE;
    
    OPEN seance;
    WHILE NOT done DO
		FETCH seance INTO current_id;
        DELETE FROM log;
		BLOCK3: BEGIN
			DECLARE answers CURSOR FOR
				SELECT seance_id, question_id, answer FROM seance_log
				WHERE seance_id = current_id;
			DECLARE CONTINUE HANDLER FOR NOT FOUND SET inner_done = TRUE;
            OPEN answers;
            WHILE NOT inner_done DO
				FETCH answers INTO se_id, q_id, ans;
                INSERT INTO log (seance_id, question_id, answer)
					VALUES (se_id, q_id, ans);
			END WHILE;
            CLOSE answers;
            -- comparison
            -- if it's the same, SET done = FALSE
		END BLOCK3;
    END WHILE;
    CLOSE seance;
END BLOCK2;
END BLOCK1
