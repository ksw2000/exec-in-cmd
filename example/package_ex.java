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
//Error: Could not find or load main class package_ex
//Caused by: java.lang.ClassNotFoundException: package_ex
//----------------------------------------------------------
//It is correct. The file has been compiled although it can't be executed.
//This file will be compiled to out/p1/package_ex.class
