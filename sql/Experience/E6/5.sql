IF(OBJECT_ID('trigcourse')IS NOT NULL )
BEGIN
    DROP TRIGGER trigcourse
END;
GO

CREATE TRIGGER trigcourse ON Course
AFTER INSERT AS
DECLARE @tempName NVARCHAR(255)
SELECT @tempName=Cname FROM inserted
IF(
    EXISTS(
        SELECT * FROM Course
        WHERE Cname=@tempName
    )
)
    BEGIN
    PRINT '已存在该课程'
    ROLLBACK
    END;
GO