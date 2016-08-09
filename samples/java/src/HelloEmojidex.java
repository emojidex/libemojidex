
import java.io.*;

import com.emojidex.libemojidex.EmojiVector;
import com.emojidex.libemojidex.HistoryItemVector;
import com.emojidex.libemojidex.Emojidex.Client;
import com.emojidex.libemojidex.Emojidex.Service.User;
import com.emojidex.libemojidex.Emojidex.Service.HistoryItem;
import com.emojidex.libemojidex.Emojidex.Data.Collection;
import com.emojidex.libemojidex.Emojidex.Data.Emoji;

public class HelloEmojidex {
    public static void main(String[] args){
        System.out.println("HelloEmojidex start."); 

        new HelloEmojidex().run();

        System.out.println("HelloEmojidex end.");
    }


    private final Client client;
    private final User user;

    private HelloEmojidex()
    {
        client = new Client();
        user = client.getUser();
    }

    private void run()
    {
      loginSample();
    }

    // ログイン
    private void loginSample()
    {
      // キーボードからログイン情報を入力
      InputStreamReader isr = new InputStreamReader(System.in);
      BufferedReader br = new BufferedReader(isr);

      String username;
      String token;
      System.out.print("username: ");
      try
      {
        username = br.readLine();
      }
      catch(IOException e)
      {
        username = "";
      }
      System.out.print("token: ");
      try
      {
        token = br.readLine();
      }
      catch(IOException e)
      {
        token = "";
      }

      // ログイン
      if(user.authorize(username, token))
        System.out.println("Login succeeded.(status = " + user.getStatus() + ")");
      else
        System.out.println("Login failed.(status = " + user.getStatus() + ")");
    }
}
