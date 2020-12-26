DROP PROCEDURE  lel;
GO

CREATE PROCEDURE lel(
    @LName  VARCHAR(20)
    )
    AS
    DECLARE lec CURSOR 
    FOR
    SELECT Bname,Ldate,Lamount,Lterm
    FROM legalEntityT,Bankt,LoanT
    WHERE legalEntityT.Eno=LoanT.Eno
    AND Bankt.Bno=LoanT.Bno
    AND legalEntityT.Ename=@LName
    ORDER BY Bname,Ldate;

    DECLARE @CBname VARCHAR(20)
    DECLARE @CLdate DATE
    DECLARE @CLamount INT
    DECLARE @CLterm SMALLINT
    PRINT @LName+'的贷款情况如下'
    PRINT '银行名称     贷款日期     贷款金额(万元)     贷款年限(年)'
    OPEN lec
    FETCH NEXT FROM lec INTO @CBname,@CLdate,@CLamount,@CLterm
    WHILE @@FETCH_STATUS=0
        BEGIN
        PRINT @CBname+'     '+CAST(@CLdate AS CHAR(10))+'     '+CAST(@CLamount AS CHAR(6))+'     '+CAST(@CLterm AS CHAR(3))
        FETCH NEXT FROM lec INTO @CBname,@CLdate,@CLamount,@CLterm;
    END
    CLOSE lec
    DEALLOCATE lec;
GO


DECLARE @EN VARCHAR(20)
DECLARE ecur CURSOR FOR
SELECT Ename FROM legalEntityT
OPEN ecur
FETCH NEXT FROM ecur INTO @EN
WHILE @@FETCH_STATUS=0
    BEGIN
    EXEC lel @LName=@EN
    FETCH NEXT FROM ecur INTO @EN
    PRINT ' '
    END 
CLOSE ecur
DEALLOCATE ecur;
GO