package algorithm;

import java.util.ArrayList;

/**
 * @author 伏特加冰糖
 */
public class MyArrayList extends ArrayList {
    public Integer[] getArray() {
        Integer[] tempList = new Integer[this.size()];
        for (int i = 0; i < this.size(); i++) {
            tempList[i] = (Integer) this.get(i);
        }
        return tempList;
    }
}
