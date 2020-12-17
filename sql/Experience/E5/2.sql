CREATE PROC VV(
    @TBname VARCHAR(20)
)
AS
if EXISTS (SELECT * FROM Bankt WHERE Bname=@TBname)
    SELECT Ename,Ldate,Lamount
    FROM legalEntityT,Bankt,LoanT
    WHERE legalEntityT.Eno=LoanT.Eno
    AND Bankt.Bno=LoanT.Bno
    AND LoanT.Lamount>(
        SELECT AVG(Lamount)
        FROM LoanT,Bankt
        WHERE LoanT.Bno=Bankt.Bno
        AND Bankt.Bname=@TBname
    ) 
ELSE
    PRINT('指定的银行不存在');
GO

DECLARE @TBname VARCHAR(20);
SET @TBname='北京分行';
EXEC VV @TBname=@TBname;
