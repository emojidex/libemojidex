
import java.io.*;

import com.emojidex.libemojidex.EmojiVector;
import com.emojidex.libemojidex.HistoryItemVector;
import com.emojidex.libemojidex.StringVector;
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
      newestSample();
      popularSample();
      followingSample();
      followersSample();
      seedSample();
    }

	// Login
    // ログイン
    private void loginSample()
    {
	  // Get login informaiton from terminal
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

	  // Perform an actual login
      // ログイン
      if(user.authorize(username, token))
        System.out.println("Login succeeded.(status = " + user.getStatus() + ")");
      else
        System.out.println("Login failed.(status = " + user.getStatus() + ")");

	  // Display some user information
      // ユーザ情報
      if(user.getStatus() == User.AuthStatusCode.VERIFIED)
      {
        System.out.println("  pro: " + user.getPro());
        System.out.println("  premium: " + user.getPremium());
      }
    }

	// Favorites
    // お気に入り
    private void favoritesSample()
    {
	  // Synchronize favorites for logged in user
      // ログイン中のユーザのお気に入りを取得
      if(user.getStatus() == User.AuthStatusCode.VERIFIED)
      {
        if(user.syncFavorites())
          System.out.println("Sync favorites succeeded.");
        else
          System.out.println("Sync favorites failed.");
      }

	  // Get favorites
      // お気に入りの絵文字の情報を取得
      Collection favorites = user.getFavorites();
      EmojiVector favorite_emoji = favorites.all();

      System.out.println("Favorites array size = " + favorite_emoji.size());
      
      System.out.println("Output favorites array:");
      for(int i = 0;  i < favorite_emoji.size();  ++i)
      {
        Emoji emoji = favorite_emoji.get(i);

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

	  // Add to favorites
      // お気に入りを追加
      if(user.addFavorite("cyclone"))
        System.out.println("Add favorite succeeded.");
      else
        System.out.println("Add favorite failed.");

	  // Remove from favorites
      // お気に入りを削除
      if(user.removeFavorite("cyclone"))
        System.out.println("Remove favorite succeeded.");
      else
        System.out.println("Remove favorite failed.");
    }

	// History
    // 履歴
    private void historySample()
    {
	  // Synchronize user history
      // ログイン中のユーザの履歴を取得
      if(user.getStatus() == User.AuthStatusCode.VERIFIED)
      {
        if(user.syncHistory().size() > 0)
          System.out.println("Sync history succeeded.");
        else
          System.out.println("Sync historyfavorites failed.");
      }

	  // Obtain user history
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

	  // Add to user history
      // 履歴を追加
      if(user.addHistory("cyclone"))
        System.out.println("Add history succeeded.");
      else
        System.out.println("Add history failed.");
    }

	// Search
    // 検索
    private void searchSample()
    {
	  // Regular search
      // 検索
      Collection searchResults = client.getSearch().term("heart");
      EmojiVector result_emoji = searchResults.all();

      System.out.println("Output search results array:");
      for(int i = 0;  i < result_emoji.size();  ++i)
      {
        Emoji emoji = result_emoji.get(i);

        System.out.println("  Search results[" + i + "].code = " + emoji.getCode());
      }

	  // Obtain next page of search results
      // 検索結果の2ページ目を取得
      searchResults.more();
      result_emoji = searchResults.all();

      System.out.println("Output search results array (page2):");
      for(int i = (int)searchResults.getOpts().getLimit();  i < result_emoji.size();  ++i)
      {
        Emoji emoji = result_emoji.get(i);

        System.out.println("  Search results[" + i + "].code = " + emoji.getCode());
      }
    }

	// Index
    // インデックス
    private void indexSample()
    {
	  // Get the main emoji Index
      // インデックス
      Collection indexes = client.getIndexes().emoji();
      EmojiVector index_emoji = indexes.all();

      System.out.println("Output index array:");
      for(int i = 0;  i < index_emoji.size();  ++i)
      {
        Emoji emoji = index_emoji.get(i);

        System.out.println("  Index[" + i + "].code = " + emoji.getCode());
      }

      // インデックスの2ページ目を取得
      indexes.more();
      index_emoji = indexes.all();

      System.out.println("Output index array (page2):");
      for(int i = (int)indexes.getOpts().getLimit();  i < index_emoji.size();  ++i)
      {
        Emoji emoji = index_emoji.get(i);

        System.out.println("  Index[" + i + "].code = " + emoji.getCode());
      }
    }

    // newest
    private void newestSample()
    {
      if(user.getPremium() == false)
        return;

      // newest
      Collection newest = client.getIndexes().newest();
      EmojiVector newest_emoji = newest.all();

      System.out.println("Output newest array:");
      for(int i = 0;  i < newest_emoji.size();  ++i)
      {
        Emoji emoji = newest_emoji.get(i);

        System.out.println("  Newest[" + i + "].code = " + emoji.getCode());
      }
    }

    // popular
    private void popularSample()
    {
      if(user.getPremium() == false)
        return;

      // popular
      Collection popular = client.getIndexes().popular();
      EmojiVector popular_emoji = popular.all();

      System.out.println("Output popular array:");
      for(int i = 0;  i < popular_emoji.size();  ++i)
      {
        Emoji emoji = popular_emoji.get(i);

        System.out.println("  Popular[" + i + "].code = " + emoji.getCode());
      }
    }

    // following
    private void followingSample()
    {
	  // Get the following list for the current user
      // ログイン中のユーザのfollowingを取得
      if(user.getStatus() == User.AuthStatusCode.VERIFIED)
      {
        if(user.syncFollowing())
          System.out.println("Sync following succeeded.");
        else
          System.out.println("Sync following failed.");
      }

	  // Add to following / follow a user
      // followingを追加
      if(user.addFollowing("絵文字デックス"))
        System.out.println("Add following succeeded.");
      else
        System.out.println("Add following failed.");

	  // Get current following list
      // followingの情報を取得
      StringVector following = user.getFollowing();

      System.out.println("Following array size = " + following.size());

      System.out.println("Output following array:");
      for(int i = 0;  i < following.size();  ++i)
      {
        String username = following.get(i);

        System.out.println("  Following[" + i + "] = " + username);
      }

	  // Remove a user from following list
      // followingを削除
      if(user.removeFollowing("絵文字デックス"))
        System.out.println("Remove following succeeded.");
      else
        System.out.println("Remove following failed.");
    }

    // followers
    private void followersSample()
    {
      if(user.getPro() == false && user.getPremium() == false)
        return;

	  // Sync the followers list for the current user
      // ログイン中のユーザのfollowersを取得
      if(user.getStatus() == User.AuthStatusCode.VERIFIED)
      {
        if(user.syncFollowers())
          System.out.println("Sync followers succeeded.");
        else
          System.out.println("Sync followers failed.");
      }


	  // Get the followers list
      // followersの情報を取得
      StringVector followers = user.getFollowers();

      System.out.println("Followers array size = " + followers.size());

      System.out.println("Output followers array:");
      for(int i = 0;  i < followers.size();  ++i)
      {
        String username = followers.get(i);

        System.out.println("  Followers[" + i + "] = " + username);
      }
    }

	// Seeds
    // シード
    private void seedSample()
    {
	  // Obtain the UTF (standard) emoji seeds
      // UTFの絵文字を取得
      Collection utfEmojiCollection = client.getIndexes().utfEmoji();
      EmojiVector utfEmojies = utfEmojiCollection.all();

      System.out.println("UTF emoji array size = " + utfEmojies.size());

      System.out.println("Output UTF emoji array:");
      for(int i = 0;  i < utfEmojies.size();  ++i)
      {
        Emoji emoji = utfEmojies.get(i);

        System.out.println("  utfEmoji[" + i + "].moji = " + emoji.getMoji());
      }

	  // Obtain the extended emoji seeds
      // extendedの絵文字を取得
      Collection extendedEmojiCollection = client.getIndexes().extendedEmoji();
      EmojiVector extendedEmojies = extendedEmojiCollection.all();

      System.out.println("Extended emoji array size = " + extendedEmojies.size());

      System.out.println("Output extended emoji array:");
      for(int i = 0;  i < extendedEmojies.size();  ++i)
      {
        Emoji emoji = extendedEmojies.get(i);

        System.out.println("  extendedEmoji[" + i + "].moji = " + emoji.getMoji());
      }
    }
}
