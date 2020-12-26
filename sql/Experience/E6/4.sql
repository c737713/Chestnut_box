/*after 触发器
IF(OBJECT_ID('triggrade_after')IS NOT NULL )
BEGIN
    DROP TRIGGER triggrade
END;
GO

CREATE TRIGGER triggrade_after ON SC
AFTER INSERT,UPDATE AS
DECLARE @tGrade FLOAT
SELECT @tGrade=Grade FROM inserted
IF(@tGrade>100)
    BEGIN
    UPDATE SC 
    SET Grade=100
    FROM SC
    WHERE SC.Grade>100
    PRINT('成绩超过上限,修订为100')
    END;
GO
*/
/*instead 触发器*/
IF(OBJECT_ID('triggrade_instead')IS NOT NULL )
BEGIN
    DROP TRIGGER triggrade
END;
GO

CREATE TRIGGER triggrade_instead ON SC
INSTEAD OF INSERT AS
DECLARE @tGrade FLOAT
SELECT @tGrade=Grade FROM inserted
IF(@tGrade>100)
    BEGIN
    DECLARE @sno FLOAT
    DECLARE @cno NVARCHAR(255)
    DECLARE @xKLB NVARCHAR(255)
    SELECT @sno=Sno FROM inserted
    SELECT @cno=Cno FROM inserted
    SELECT @xKLB=XKLB FROM inserted
    INSERT INTO SC
    VALUES(@sno,@cno,100,@xKLB)
    PRINT('成绩超过上限,修订为100')
    END;
GO



/*在SQL server下的instead触发器,在触发后不会执行触发其的语句
在SQL server下的after触发器,在触发后会执行触发其的语句
thus,instead不能同时对instead与update起效*/

