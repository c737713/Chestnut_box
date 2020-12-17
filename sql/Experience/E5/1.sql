CREATE PROC DD(
    @TLdate DATE,
    @TEname VARCHAR(20)
)
AS
DELETE FROM LoanT
FROM LoanT,legalEntityT
WHERE LoanT.Eno=legalEntityT.Eno
AND LoanT.Ldate<@TLdate
AND legalEntityT.Ename=@TEname
GO;

DECLARE @TLdate DATE;
DECLARE @TEname VARCHAR(20);
SET @TLdate='2010-10-01';
SET @TEname='新都美百货公司'
EXEC DD @TLdate=@TLdate,@TEname=@TEname;
