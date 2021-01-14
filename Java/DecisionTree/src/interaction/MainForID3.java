package interaction;


import algorithm.DataBase;
import algorithm.Id3Tree;

/**
 * @author Mr Chippy
 */
public class MainForID3 {
    public static void main(String[] args) {
        DataBase dataBase = DataBase.getDataBaseByFile("D:\\gitArea\\Chestnut_box\\Java\\DecisionTree\\src\\datasource\\a.txt");
        DataBase dataBase1 = DataBase.getDataBaseByFile("D:\\gitArea\\Chestnut_box\\Java\\DecisionTree\\src\\datasource\\b.txt");
        Id3Tree id3Tree = new Id3Tree(dataBase);
        id3Tree.setForTestingData(dataBase1);
        id3Tree.examination();
    }
}
