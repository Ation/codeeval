using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.IO.Compression;

internal class FriendsCounter
{
    public FriendsCounter()
    {
        m_usedWords = new HashSet<string>();
        m_vocabulary = new HashSet<string>();
        m_wordsToCheckList = new List<string>();

        m_counter = 0;
    }

    public void ResetCounter(string starterWord)
    {
        m_counter = 1;
        m_usedWords.Clear();
        m_wordsToCheckList.Clear();

        m_usedWords.Add(starterWord);
        m_wordsToCheckList.Add(starterWord);
    }

    public void AddVocabularyWord(String word)
    {
        m_vocabulary.Add(word);
    }

    public int FriendCount { get { return m_counter; } }

    public Boolean HaveCandidats()
    {
        return m_wordsToCheckList.Count() != 0;
    }

    public string GetNextCandidate()
    {
        if (m_wordsToCheckList.Count() != 0)
        {
            String result = m_wordsToCheckList[0];
            m_wordsToCheckList.RemoveAt(0);
            return result;
        }
        return String.Empty;
    }

    public void AddFriend(String friendWord)
    {
        if (m_vocabulary.Contains(friendWord))
        {
            if (!m_usedWords.Contains(friendWord))
            {
                m_usedWords.Add(friendWord);
                m_wordsToCheckList.Add(friendWord);
                m_counter++;
            }
        }
    }

    #region Fields

    private int m_counter;

    private readonly HashSet<String> m_usedWords;
    private readonly HashSet<String> m_vocabulary;
    private readonly List<String> m_wordsToCheckList;

#endregion
}

namespace set_cs
{
    class Program
    {
        static int Main(string[] args)
        {
            if (args.Count() != 1)
            {
                return 1;
            }

            List<String> testCases = new List<string>();
            FriendsCounter counter = new FriendsCounter();
            const string marker = "END OF INPUT";

            using (var reader = File.OpenText(args[0]))
            {
                string line;

                // read test cases
                while ((line = reader.ReadLine()) != null)
                {
                    if (line == marker)
                    {
                        break;
                    }

                    testCases.Add(line);
                }

                // read vocabulary
                while ((line = reader.ReadLine()) != null)
                {
                    counter.AddVocabularyWord(line);
                }
            }

            foreach (string testCase in testCases)
            {
                counter.ResetCounter(testCase);

                while (counter.HaveCandidats())
                {
                    string word = counter.GetNextCandidate();
                    string checkThis;

                    // removals
                    if (word.Length > 1)
                    {
                        checkThis = word.Substring(1);
                        counter.AddFriend(checkThis);

                        checkThis = word.Substring(0, word.Length - 1);
                        counter.AddFriend(checkThis);
                    }

                    for (Int32 i = 1; i < word.Length - 1; i++)
                    {
                        checkThis = word.Substring(0, i) + word.Substring(i + 1, word.Length - i - 1);
                        counter.AddFriend(checkThis);
                    }

                    // replacements
                    if (word.Length == 1)
                    {
                        char originalSymbol = word[0];

                        for (char symbol = 'a'; symbol <= 'z'; ++symbol)
                        {
                            if (symbol != originalSymbol)
                            {
                                checkThis = symbol.ToString();
                                counter.AddFriend(checkThis);
                            }
                        }
                    }
                    else
                    {
                        StringBuilder strBuilder = new StringBuilder(word);

                        for (int i = 0; i < word.Length; ++i)
                        {
                            char originalSymbol = word[i];

                            for (char symbol = 'a'; symbol <= 'z'; ++symbol)
                            {
                                if (symbol != originalSymbol)
                                {
                                    strBuilder[i] = symbol;
                                    counter.AddFriend(strBuilder.ToString());
                                }
                            }

                            strBuilder[i] = originalSymbol;
                        }
                    }

                    // insertions
                    for (int i = 0; i <= word.Length; ++i)
                    {
                        StringBuilder strBuilder = new StringBuilder(word);
                        strBuilder.Insert(i, 'a');

                        for (char symbol = 'a'; symbol <= 'z'; ++symbol)
                        {
                            strBuilder[i] = symbol;
                            counter.AddFriend(strBuilder.ToString());
                        }
                    }

                }

                Console.WriteLine(counter.FriendCount);
            }

            return 0;
        }
    }
}
