package Main;

import com.sun.jna.Native;
import com.sun.jna.Structure;
import com.sun.jna.platform.win32.BaseTSD;
import com.sun.jna.platform.win32.WinDef;
import com.sun.jna.win32.StdCallLibrary;
import com.sun.jna.win32.W32APIOptions;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public
class AutoTyper
{

    // ----------------- 常量 -----------------
    public static final int INPUT_KEYBOARD    = 1;
    public
    static final        int KEYEVENTF_UNICODE = 0x0004;
    public
    static final        int VK_RETURN         = 0x0D;
    public
    static final        int VK_TAB            = 0x09;
    public
    static final        int VK_SPACE          = 0x20;
    public
    static final        int VK_DELETE         = 0x2E;
    public
    static final        int VK_HOME           = 0x24;


    static final String file_path = ".ignore/src.txt";

    // ----------------- 工具函数 -----------------
    private
    static
    void sendUnicodeChar(char c)
    {
        INPUT in = new INPUT();
        in.type       = new WinDef.DWORD(INPUT_KEYBOARD);
        in.ki         = new KEYBDINPUT();
        in.ki.wScan   = new WinDef.WORD(c);
        in.ki.dwFlags = new WinDef.DWORD(KEYEVENTF_UNICODE);
        User32.INSTANCE.SendInput(1, new INPUT[] {in}, in.size());
    }

    private
    static
    void sendVK(int vk)
    {
        INPUT in = new INPUT();
        in.type   = new WinDef.DWORD(INPUT_KEYBOARD);
        in.ki     = new KEYBDINPUT();
        in.ki.wVk = new WinDef.WORD(vk);
        User32.INSTANCE.SendInput(1, new INPUT[] {in}, in.size());
    }

    private
    static
    boolean keyDown(int vk)
    {
        return (User32.INSTANCE.GetKeyState(vk) & 0x8000) != 0;
    }

    private
    static
    List<Character> loadFile(String path)
    {
        System.out.println("pwd" + new File(".").getAbsolutePath());
        System.out.println("path:" + path);
        List<Character> result = new ArrayList<>();
        try(Reader reader = new InputStreamReader(new FileInputStream(path), Charset.defaultCharset()))
        {
            int c;
            while((c = reader.read()) != -1)
            {
                result.add((char) c);
            }
        }
        catch(Exception e)
        {
            System.out.println("error");
        }
        return result;
    }

    // ----------------- Copy -----------------
    public
    static
    void Copy() throws Exception
    {
        List<Character> chars = loadFile(file_path);
        System.out.println("按下Enter开始抄写...");
        while(!keyDown(VK_RETURN)) ;
        while(keyDown(VK_RETURN)) ;

        System.out.println("==========================================================");

        for(char c : chars)
        {
            System.out.print(c);

            switch(c)
            {
            case '\n':
                sendVK(VK_RETURN);
                break;
            case '\t':
                sendVK(VK_TAB);
                break;
            default:
                sendUnicodeChar(c);
                break;
            }

            if(keyDown(VK_SPACE))
                break;

            Thread.sleep(1);
        }

        System.out.println("\n==========================================================\n抄写结束");
    }

    // ----------------- MCopy -----------------
    public
    static
    void MCopy() throws Exception
    {
        List<Character> chars = loadFile(file_path);
        System.out.println("按下Enter开始适应抄写...");
        while(!keyDown(VK_RETURN)) ;
        while(keyDown(VK_RETURN)) ;

        System.out.println("==========================================================");

        for(char c : chars)
        {
            System.out.print(c);

            switch(c)
            {
            case '{':
            case '[':
            case '(':
                sendUnicodeChar(c);
                sendVK(VK_DELETE);
                break;

            case '\n':
                sendUnicodeChar(' ');
                sendVK(VK_RETURN);
                sendVK(VK_HOME);
                break;

            default:
                sendUnicodeChar(c);
                break;
            }

            if(keyDown(VK_SPACE))
                break;

            Thread.sleep(1);
        }

        System.out.println("\n==========================================================\n抄写结束");
    }

    // ----------------- CCopy -----------------
    public
    static
    void CCopy() throws Exception
    {
        List<Character> chars = loadFile(file_path);
        System.out.println("按下Enter开始适应抄写（不换行模式）...");
        while(!keyDown(VK_RETURN)) ;
        while(keyDown(VK_RETURN)) ;

        System.out.println("==========================================================");

        boolean isSpace = true;
        boolean isIn    = false;

        for(char c : chars)
        {
            System.out.print(c);

            switch(c)
            {
            case '#':
                isIn = true;
                sendVK(VK_RETURN);
                sendVK(VK_HOME);
                sendUnicodeChar(c);
                break;

            case '\n':
                if(isIn)
                {
                    isIn = false;
                    sendVK(VK_RETURN);
                    sendVK(VK_HOME);
                }
                break;

            case ' ':
                if(isSpace)
                {
                    isSpace = false;
                    sendUnicodeChar(c);
                }
                break;

            default:
                isSpace = true;
                sendUnicodeChar(c);
                break;
            }

            if(keyDown(VK_SPACE))
                break;

            Thread.sleep(1);
        }

        System.out.println("\n==========================================================\n抄写结束");
    }

    // ----------------- 主菜单 -----------------
    public
    static
    void fun_01() throws Exception
    {
        int i = 0;
        while(i != 'q')
        {
            System.out.println("按下'N'键开始读取");
            System.out.println("按下'M'键开始适应读取");
            System.out.println("按下'C'键开始不换行读取");
            System.out.println("按下'Q'键退出...");

            i = System.in.read();

            switch(i)
            {
            case 'n': Copy();
                break;
            case 'm': MCopy();
                break;
            case 'c': CCopy();
                break;
            default: break;
            }
        }

        System.out.println("程序已退出");
    }

    public
    static
    void main(String[] args) throws Exception
    {
        System.out.println("start");
        fun_01();
    }

    // ----------------- Win32 API 接口 -----------------
    public
    interface User32 extends StdCallLibrary
    {
        User32 INSTANCE = Native.load("user32", User32.class, W32APIOptions.DEFAULT_OPTIONS);

        short GetKeyState(int key);

        void SendInput(int nInputs, INPUT[] pInputs, int cbSize);
    }

    public
    static
    class INPUT extends Structure
    {
        public
        WinDef.DWORD type;
        public
        KEYBDINPUT   ki;

        @Override
        protected
        List<String> getFieldOrder()
        {
            return Arrays.asList("type", "ki");
        }

        public
        static
        class ByReference extends INPUT implements Structure.ByReference { }
    }

    public static
    class KEYBDINPUT extends Structure
    {
        public
        WinDef.WORD       wVk;
        public
        WinDef.WORD       wScan;
        public
        WinDef.DWORD      dwFlags;
        public
        WinDef.DWORD      time;
        public
        BaseTSD.ULONG_PTR dwExtraInfo;

        @Override
        protected
        List<String> getFieldOrder()
        {
            return Arrays.asList("wVk", "wScan", "dwFlags", "time", "dwExtraInfo");
        }
    }
}
