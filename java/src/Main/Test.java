package Main;

import java.awt.*;
import java.awt.event.KeyEvent;

public
class Test
{
    public static
    void main(String[] args)
    {
        try
        {
            // 1. 创建 Robot 实例
            Robot robot = new Robot();

            // 可选：等待几秒，给用户时间切换到目标窗口
            // 比如，切换到记事本或浏览器
            System.out.println("请在 3 秒内切换到目标输入框...");
            robot.delay(3000); // 延迟

            // 2. 模拟输入文本 "Hello World!"
            String text = "Hello World!";
            simulateTyping(robot, text);

            // 3. 模拟按下 Enter 键
            robot.keyPress(KeyEvent.VK_ENTER);
            robot.keyRelease(KeyEvent.VK_ENTER);

        }
        catch(AWTException e)
        {
            System.err.println("创建 Robot 实例失败，可能缺少必要的权限:" + e.getMessage());
        }
    }

    /**
     * 模拟输入指定的字符串。
     * * @param robot Robot 实例
     *
     * @param text 要输入的字符串
     */
    public static
    void simulateTyping(Robot robot, String text)
    {
        for(char c : text.toCharArray())
        {
            try
            {
                int keyCode = KeyEvent.getExtendedKeyCodeForChar(c);

                // 检查是否需要 Shift 键 (比如大写字母或特殊符号)
                if(Character.isUpperCase(c) || isSpecialCharacter(c))
                {
                    robot.keyPress(KeyEvent.VK_SHIFT);
                }

                // 模拟按键按下和释放
                robot.keyPress(keyCode);
                robot.keyRelease(keyCode);

                // 释放 Shift 键
                if(Character.isUpperCase(c) || isSpecialCharacter(c))
                {
                    robot.keyRelease(KeyEvent.VK_SHIFT);
                }

                // 可选：稍微延迟，让输入更自然
                robot.delay(50);

            }
            catch(IllegalArgumentException e)
            {
                // 如果找不到字符的 KeyCode，跳过该字符
                System.err.println("无法模拟字符: `" + c + "`");
            }
        }
    }

    /**
     * 简单的辅助方法来判断一些需要 Shift 键的特殊字符。
     */
    private static
    boolean isSpecialCharacter(char c)
    {
        // 这只是一个不完整的示例，实际应用中需要更全面的映射
        return c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*' || c == '(' || c == ')';
    }
}