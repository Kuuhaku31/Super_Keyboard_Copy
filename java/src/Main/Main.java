package Main;


import java.io.File;

public
class Main
{
    public

    static
    void main(String[] args)
    {
        var message = "Hello, 中文!";
        System.out.println(message);
        System.out.println(new File(".").getAbsolutePath());
        for(var i = 0; i < 5; i++)
        {
            System.out.println("Count: " + i);
        }
        System.out.println("Bye!");
    }
}