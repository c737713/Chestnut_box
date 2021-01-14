package algorithm;

import java.util.ArrayList;

/**
 * @author 伏特加冰糖
 */
public class TreeNode {
    String outPut;
    Boolean leafValue;
    String attribute;

    ArrayList<Integer> indexList;
    ArrayList<TreeNode> childList;

    public TreeNode() {
        outPut = null;
        leafValue = null;
        indexList = new ArrayList<>();
        childList = null;
        attribute = null;
    }
}
