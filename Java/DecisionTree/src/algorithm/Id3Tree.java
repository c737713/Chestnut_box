package algorithm;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Objects;
import java.util.Queue;

import static java.lang.String.format;

/**
 * @author 伏特加冰糖
 */
public class Id3Tree {
    DataBase forTrainingData;
    DataBase forTestingData;

    public void setForTestingData(DataBase forTestingData) {
        this.forTestingData = forTestingData;
    }

    TreeNode root;

    public Id3Tree(DataBase forTrainingData) {
        this.forTrainingData = forTrainingData;
        root = new TreeNode();
        if (forTrainingData.tupleArrayList.size() == 0) {
            System.out.println("非法字符");
            root = null;
            return;
        } else if (forTrainingData.tupleArrayList.size() == 1) {
            root.outPut = forTrainingData.tupleArrayList.get(0).labelValue;
            root.leafValue = root.outPut;
        }
        root.indexList = new ArrayList<>();
        root.outPut = "根节点";
        for (int i = 0; i < forTrainingData.tupleArrayList.size(); i++) {
            root.indexList.add(i);
        }
        createTree();
    }

    public void createTree() {
        Queue<TreeNode> nodeQueue = new LinkedList<>();
        nodeQueue.add(root);
        while (!nodeQueue.isEmpty()) {
            TreeNode tempNode = nodeQueue.remove();
            Status tempStatus = forTrainingData.availableA(tempNode.indexList);
            if (tempStatus.oneStatus) {
                tempNode.leafValue = forTrainingData.tupleArrayList.get(tempNode.indexList.get(0)).labelValue;
                tempNode.attribute = "叶子节点";
                tempNode.indexList = null;
            } else {
                Attribute attribute = forTrainingData.highestInfoGainIndex(tempStatus.aList, tempNode.indexList);
                tempNode.attribute = attribute.name;
                tempNode.childList = new ArrayList<>();
                for (int i = 0; i < attribute.optionLists.size(); i++) {
                    TreeNode childNode = new TreeNode();
                    childNode.outPut = attribute.optionLists.get(i).optionName;
                    childNode.indexList = attribute.optionLists.get(i).indexList;
                    tempNode.childList.add(childNode);
                    nodeQueue.offer(childNode);
                }
            }
        }
        System.out.println("决策树构建完成");
        this.verification();
    }

    /**
     * @apiNote 层序遍历决策树
     */
    public void printTree() {
        Queue<TreeNode> tempQueue = new LinkedList<>();
        TreeNode cur ;
        tempQueue.add(root);
        while (!tempQueue.isEmpty()) {
            cur = tempQueue.remove();
            String out;
            if(cur.leafValue==null){
                out=format("{(%s)%s}",cur.attribute,cur.outPut);
            }else{
                out=format("{(%s)%s}",cur.leafValue,cur.outPut);
            }
            System.out.println(out);
            if (cur.leafValue == null) {
                for (int i = 0, length = cur.childList.size(); i < length; i++) {
                    tempQueue.add(cur.childList.get(i));
                }
            }
        }
        System.out.println("遍历完成");
    }

    public TestResult test(Tuple target) throws SecondException{
        if(target.infoList.length!=this.forTrainingData.stringArrayList.size()){
            throw new SecondException("待测试数据集列数错误");
        }
        TestResult resultSet=new TestResult();
        resultSet.deepValues=1;
        TreeNode cur=this.root;
        while(cur.leafValue==null){
            int flag=this.forTrainingData.attributeIndex(cur.attribute);
            resultSet.deepValues++;
            for (int i = 0; i < cur.childList.size(); i++) {
                if(target.infoList[flag].equals(cur.childList.get(i).outPut)){
                    cur=cur.childList.get(i);
                    break;
                }
            }
        }
        resultSet.decisionRes = cur.leafValue;
        resultSet.resourceRes = target.labelValue;
        return resultSet;
    }

    public void testing(DataBase target){
        StringBuffer sb=new StringBuffer("验证:");
        int deep = 0;
        boolean correct=true;
        ArrayList<ErrorResult> errorList = new ArrayList<>();
        try{
            for (int i = 0; i < target.tupleArrayList.size(); i++) {
                TestResult ts=this.test(target.tupleArrayList.get(i));
                if(ts.deepValues>deep){
                    deep= ts.deepValues;
                }
                if(!Objects.equals(ts.decisionRes, ts.resourceRes)){
                    correct=false;
                    errorList.add(new ErrorResult(ts.decisionRes,i));
                }
            }
        }catch (SecondException e){
            e.printStackTrace();
        }
        sb.append(" 树的深度为:").append(deep);
        if(correct){
            sb.append(",且验证结果符合要求");
            System.out.println(sb);
        }else{
            sb.append(",可是验证结果错误,出错的结果集如下:");
            System.out.println(sb);
            for (int i = 0; i < errorList.size(); i++) {
                for (int i1 = 0; i1 < target.tupleArrayList.get(errorList.get(i).index).infoList.length; i1++) {
                    System.out.print(target.tupleArrayList.get(i).infoList[i1]+" ");
                }
                System.out.printf("原数据集上的标签值为%s,而决策的结果与其不一致,为%s",
                        target.tupleArrayList.get(errorList.get(i).index).labelValue,
                        errorList.get(i).errorInfo);
            }
        }
    }

    public void verification(){
        System.out.println("对于自身数据集的验证:");
        this.testing(this.forTrainingData);
    }

    public void examination(){
        System.out.println("对于测试集的验证:");
        this.testing(this.forTestingData);
    }
}
