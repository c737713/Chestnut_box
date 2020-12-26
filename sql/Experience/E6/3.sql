IF(OBJECT_ID('trigsex') IS NOT NULL )
BEGIN
DROP TRIGGER trigsex
END;
GO

CREATE TRIGGER trigsex ON Student
AFTER INSERT,UPDATE 
AS
DECLARE @newsex VARCHAR(10)
SELECT Ssex
FROM INSERTED
IF(@newsex!='男' or @newsex!='女')
    BEGIN
    PRINT '非法性别'
    ROLLBACK
    END;
GO
/*触发器1*/
/*在sql中begin与end的关系类似于C/java中的花括号*/
