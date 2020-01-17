        IDENTIFICATION DIVISION.
        PROGRAM-ID. ABC150_A.
      
        ENVIRONMENT DIVISION.
      
        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01 K PIC 9(15).
        01 X PIC 9(15).
        01 TMP PIC 9(15).
        01 INPUT_LINE PIC X(15).
        01 P1 PIC 9 VALUE 1.
        01 P2 PIC 9.
      
        PROCEDURE DIVISION.
        MAIN.
            ACCEPT INPUT_LINE.
            PERFORM VARYING P2 FROM 1 BY 1
                UNTIL INPUT_LINE(P1 + P2:1) = SPACE
            END-PERFORM
            MOVE INPUT_LINE(P1:P2) TO K
            ADD P2+1 TO P1

            PERFORM VARYING P2 FROM 1 BY 1
                UNTIL INPUT_LINE(P1 + P2:1) = SPACE
            END-PERFORM
            MOVE INPUT_LINE(P1:P2) TO X

            COMPUTE TMP = 500 * K.
            IF TMP >= X THEN
                DISPLAY "Yes"
            ELSE
                DISPLAY "No"
            END-IF

            STOP RUN.
