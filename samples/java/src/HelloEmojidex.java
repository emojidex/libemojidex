
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
      favoritesSample();
      historySample();
      searchSample();
      indexSample();
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

    // お気に入り
    private void favoritesSample()
    {
      // ログイン中のユーザのお気に入りを取得
      if(user.getStatus() == User.AuthStatusCode.VERIFIED)
      {
        if(user.syncFavorites())
          System.out.println("Sync favorites succeeded.");
        else
          System.out.println("Sync favorites failed.");
      }

      // お気に入りの絵文字の情報を取得
      Collection favorites = user.getFavorites();
      EmojiVector emojies = favorites.all();

      System.out.println("Favorites array size = " + emojies.size());
      
      System.out.println("Output favorites array:");
      for(int i = 0;  i < emojies.size();  ++i)
      {
        Emoji emoji = emojies.get(i);

        // System.out.println("  Favorites[" + i + "].moji = " + emoji.getMoji());
        System.out.println("  Favorites[" + i + "].code = " + emoji.getCode());
        // System.out.println("  Favorites[" + i + "].unicode = " + emoji.getUnicode());
        // System.out.println("  Favorites[" + i + "].category = " + emoji.getCategory());
        // System.out.println("  Favorites[" + i + "].tags = " + emoji.getTags());
        // System.out.println("  Favorites[" + i + "].base = " + emoji.getBase());
        // System.out.println("  Favorites[" + i + "].variants = " + emoji.getVariants());
        // System.out.println("  Favorites[" + i + "].link = " + emoji.getLink());
        // System.out.println("  Favorites[" + i + "].is_wide = " + emoji.getIs_wide());
        // System.out.println("  Favorites[" + i + "].copyright_lock = " + emoji.getCopyright_lock());
        // System.out.println("  Favorites[" + i + "].times_used = " + emoji.getTimes_used());
        // System.out.println("  Favorites[" + i + "].times_favorited = " + emoji.getTimes_favorited());
        // System.out.println("  Favorites[" + i + "].score = " + emoji.getScore());
        // System.out.println("  Favorites[" + i + "].attribution = " + emoji.getAttribution());
        // System.out.println("  Favorites[" + i + "].user_id = " + emoji.getUser_id());
        // System.out.println("  Favorites[" + i + "].current_price = " + emoji.getCurrent_price());
        // System.out.println("  Favorites[" + i + "].primary = " + emoji.getPrimary());
        // System.out.println("  Favorites[" + i + "].permalock = " + emoji.getPermalock());
        // System.out.println("  Favorites[" + i + "].registered_at = " + emoji.getRegistered_at());
        // System.out.println("  Favorites[" + i + "].link_expiration = " + emoji.getLink_expiration());
        // System.out.println("  Favorites[" + i + "].lock_expiration = " + emoji.getLock_expiration());
        // System.out.println("  Favorites[" + i + "].times_changed = " + emoji.getTimes_changed());
        // System.out.println("  Favorites[" + i + "].favorited = " + emoji.getFavorited());
        // System.out.println("  Favorites[" + i + "].checksums = " + emoji.getChecksums());
      }

      // お気に入りを追加
      if(user.addFavorite("cyclone"))
        System.out.println("Add favorite succeeded.");
      else
        System.out.println("Add favorite failed.");

      // お気に入りを削除
      if(user.removeFavorite("cyclone"))
        System.out.println("Remove favorite succeeded.");
      else
        System.out.println("Remove favorite failed.");
    }

    // 履歴
    private void historySample()
    {
      // ログイン中のユーザの履歴を取得
      if(user.getStatus() == User.AuthStatusCode.VERIFIED)
      {
        if(user.syncHistory().size() > 0)
          System.out.println("Sync history succeeded.");
        else
          System.out.println("Sync historyfavorites failed.");
      }

      // 履歴の絵文字の情報を取得
      HistoryItemVector historyItems = user.getHistory();

      System.out.println("History array size = " + historyItems.size());
      
      System.out.println("Output history array:");
      for(int i = 0;  i < historyItems.size();  ++i)
      {
        HistoryItem historyItem = historyItems.get(i);

        System.out.println("  History[" + i + "].emoji_code = " + historyItem.getEmoji_code());
        // System.out.println("  History[" + i + "].times_used = " + historyItem.getTimes_used());
        // System.out.println("  History[" + i + "].last_used = " + historyItem.getLast_used());
      }

      // 履歴を追加
      if(user.addHistory("cyclone"))
        System.out.println("Add history succeeded.");
      else
        System.out.println("Add history failed.");
    }

    // 検索
    private void searchSample()
    {
      // 検索
      Collection searchResults = client.getSearch().term("heart");
      EmojiVector emojies = searchResults.all();

      System.out.println("Output search results array:");
      for(int i = 0;  i < emojies.size();  ++i)
      {
        Emoji emoji = emojies.get(i);

        System.out.println("  Search results[" + i + "].code = " + emoji.getCode());
      }

      // 検索結果の2ページ目を取得
      searchResults.more();
      emojies = searchResults.all();

      System.out.println("Output search results array (page2):");
      for(int i = (int)searchResults.getOpts().getLimit();  i < emojies.size();  ++i)
      {
        Emoji emoji = emojies.get(i);

        System.out.println("  Search results[" + i + "].code = " + emoji.getCode());
      }
    }

    // インデックス
    private void indexSample()
    {
      // インデックス
      Collection indexes = client.getIndexes().emoji();
      EmojiVector emojies = indexes.all();

      System.out.println("Output index array:");
      for(int i = 0;  i < emojies.size();  ++i)
      {
        Emoji emoji = emojies.get(i);

        System.out.println("  Index[" + i + "].code = " + emoji.getCode());
      }

      // インデックスの2ページ目を取得
      indexes.more();
      emojies = indexes.all();

      System.out.println("Output index array (page2):");
      for(int i = (int)indexes.getOpts().getLimit();  i < emojies.size();  ++i)
      {
        Emoji emoji = emojies.get(i);

        System.out.println("  Index[" + i + "].code = " + emoji.getCode());
      }
    }
}
