CREATE PROCEDURE `choose` (OUT q INT)
BEGIN
	DECLARE p_sol, p DOUBLE;
    DECLARE h_max DOUBLE DEFAULT 0;
    DECLARE f_count INT;
	-- containers
	DECLARE q_id, sol_id, ans INT;
    -- temporary tables
    CREATE TEMPORARY TABLE filtered (
        seance_id INT,
        solution_id INT,
        count INT);
    CREATE TEMPORARY TABLE probs (
        solution_id INT,
        priori DOUBLE);
    -- self-explanatory
    DECLARE cur_q CURSOR FOR
        SELECT question_id FROM questions;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    DECLARE cur_s CURSOR FOR
        SELECT solution_id FROM solutions;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET inner_done = TRUE;

    OPEN cur_q;
    WHILE NOT done DO
		FETCH cur_q INTO q_id;
        -- filter seances
        -- by presence of current question
        DELETE * FROM filtered;
        SELECT IF( EXISTS(
            SELECT seance_id FROM seance_log
            WHERE question_id = q_id
        ),  SELECT * FROM seances
            WHERE seance_id IN (
                SELECT DISTINCT seance_id FROM seance_log
                WHERE question_id = q_id
        ), SELECT * FROM seances);
        SELECT COUNT(*) FROM filtered INTO f_count;
        -- calculate solution probabilities
        -- based on seance count in filtered table
        DELETE * FROM probs;
        OPEN cur_s;
        WHILE NOT inner_done DO
            FETCH cur_s INTO sol_id;
            INSERT INTO probs (solution_id, priori)
            SELECT sol_id, count/f_count
            FROM filtered
            WHERE solution_id = sol_id;
        END WHILE;
        SET inner_done = TRUE;
        -- calculate answer probability
        -- based on aforementioned (and calculated) priori
        -- and answer probability given that solution is right
        SET ans = 0;
        SET h = 0;
        WHILE ans < 5 DO
            SET ans = ans + 1;
            SELECT SUM(count)*priori/f_count
            FROM filtered INNER JOIN probs
            ON filtered.seance_id = probs.seance_id
            WHERE seance_id IN (
                SELECT DISTINCT seance_id
                FROM seance_log
                WHERE answer = ans
            ) INTO p;
            SET h = h - p * LOG(p);
        END WHILE;
        SELECT IF (h > h_max, q_id) INTO q;
        SELECT IF (h > h_max, h, h_max) INTO h_max;
    END WHILE;
END
