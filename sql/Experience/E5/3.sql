DROP PROCEDURE  sumAmount;
GO
CREATE PROC sumAmount(
    @TEname VARCHAR(20)='赛纳网络有限公司'
)
    AS
    IF(
        EXISTS (
            SELECT legalEntityT.Ename 
            FROM legalEntityT,LoanT
            WHERE LoanT.Eno=legalEntityT.Eno
            )
        )
    SELECT SUM(LoanT.Lamount) AS 贷款总金额
    FROM LoanT,legalEntityT
    WHERE legalEntityT.Eno=LoanT.Eno
    AND legalEntityT.Ename=@TEname;
    ELSE
    PRINT('此法人无贷款记录');
    GO

EXEC sumAmount ;

