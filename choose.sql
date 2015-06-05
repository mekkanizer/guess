CREATE PROCEDURE `choose` (OUT q INT)
BEGIN
	DECLARE p_sol, p DOUBLE;
    DECLARE h DOUBLE DEFAULT 0;
    DECLARE h_max DOUBLE DEFAULT -10;
    DECLARE se_id INT;
    -- iterator
    DECLARE ans INT DEFAULT 0;
	-- containers
	DECLARE q_id, sol_id, t INT;
    -- self-explanatory
    DECLARE pair CURSOR FOR
        SELECT question_id, solution_id, times
            FROM questions CROSS JOIN solutions;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	
    OPEN pair;
    WHILE NOT done DO 
		FETCH pair INTO q_id, sol_id, t;
        -- step 1
        SELECT COUNT(*) INTO priori;
        SET priori = t / priori;
        -- step 2
        CREATE TEMPORARY TABLE filtered AS
        SELECT seance_id FROM seance_log
            WHERE question_id = q_id
            INTO se_id;
        /* step 2 (altered)
        SELECT seance_id FROM seances
            WHERE solution = sol_id
            INTO se_id;
        */
        -- step 3 and remaining
        WHILE ans < 4 DO
            SELECT COUNT(*) / 4 FROM seance_log
                WHERE question_id = q_id
                AND seance_id IN (
                    SELECT seance_id from filtered
                ) INTO p;
            SET p = p * p_sol;
            SET h = h - p * LOG(p);
            SELECT IF (h > h_max, q_id) INTO q;
            SELECT IF (h > h_max, h, h_max) INTO h_max;
            SET ans = ans + 1;
        END WHILE;
        SET h = 0;
	END WHILE;
END