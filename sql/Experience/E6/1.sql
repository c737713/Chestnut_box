
DROP PROCEDURE  BankLon;
GO

CREATE PROCEDURE BankLon(
    @BankName  VARCHAR(20)
    )
    AS
    DECLARE Bank_Cur CURSOR 
    FOR
    SELECT Ename,Ldate,Lamount,Lterm
    FROM legalEntityT,Bankt,LoanT
    WHERE legalEntityT.Eno=LoanT.Eno
    AND Bankt.Bno=LoanT.Bno
    AND Bankt.Bname=@BankName
    ORDER BY Ename,Ldate;

    DECLARE @CEname VARCHAR(20)
    DECLARE @CLdate DATE
    DECLARE @CLamount INT
    DECLARE @CLterm SMALLINT
    PRINT @BankName+'的贷款情况如下'
    PRINT '法人名称     贷款日期     贷款金额(万元)     贷款年限(年)'
    OPEN Bank_cur
    FETCH NEXT FROM Bank_cur INTO @CEname,@CLdate,@CLamount,@CLterm
    WHILE @@FETCH_STATUS=0
        BEGIN
        PRINT @CEname+'     '+CAST(@CLdate AS CHAR(10))+'     '+CAST(@CLamount AS CHAR(6))+'     '+CAST(@CLterm AS CHAR(3))
        FETCH NEXT FROM Bank_cur INTO @CEname,@CLdate,@CLamount,@CLterm;
    END
    CLOSE Bank_cur
    DEALLOCATE Bank_cur;
GO


DECLARE @BN VARCHAR(20)
DECLARE bankcur CURSOR FOR
SELECT Bname FROM Bankt
OPEN bankcur
FETCH NEXT FROM bankcur INTO @BN
WHILE @@FETCH_STATUS=0
    BEGIN
    EXEC BankLon @BankName=@BN
    FETCH NEXT FROM bankcur INTO @BN
    PRINT ' '
    END 
CLOSE Bankcur
DEALLOCATE Bankcur;
GO


