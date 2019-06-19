//This is an example for using package in java
//We will use exec-in-cmd/lib/readPackage.exe to search keyword "package" in this java file
package p1;
public class package_ex{
    public static void p(){
        System.out.print("A function in package");
    }
}
//If you click F12 , you will get:
//----------------------------------------------------------
//Error: Main method not found in class p1.package_ex, please define the main method as:
//   public static void main(String[] args)
//or a JavaFX application class must extend javafx.application.Application
//----------------------------------------------------------
//It is correct. The file has been compiled although it can't be executed.
//This file will be compiled to out/p1/package_ex.class
