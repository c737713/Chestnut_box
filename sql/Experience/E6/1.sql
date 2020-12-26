/*
DROP PROCEDURE BankLon;
GO
*/

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
    PRINT '法人名称\t贷款日期\t贷款金额(万元)\t贷款年限(年)'
    OPEN Bank_cur
    FETCH NEXT FROM Bank_cur INTO @CEname,@CLdate,@CLamount,@CLterm
    WHILE @@FETCH_STATUS=0
        BEGIN
        PRINT @CEname+'\t'+CAST(@CLdate AS CHAR(10))+'\t'+CAST(@CLamount AS CHAR(6))+'\t'+CAST(@CLterm AS CHAR(3))
        FETCH NEXT FROM Bank_cur INTO @CEname,@CLdate,@CLamount,@CLterm
GO


DECLARE @BankName VARCHAR(20)


