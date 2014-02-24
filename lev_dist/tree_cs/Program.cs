using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace tree_cs
{
    internal class FriendsCounter
    {

        public FriendsCounter()
        {
            m_usedWords = new HashSet<string>();
            m_wordsToCheck = new Queue<string>();
        }

        public void Reset()
        {
            m_usedWords.Clear();
            m_wordsToCheck.Clear();
        }

        public Boolean AddFriend(string word)
        {
            if (m_usedWords.Contains(word)) return false;

            m_usedWords.Add(word);
            m_wordsToCheck.Enqueue(word);

            return true;
        }

        public Boolean HaveWordsToCheck
        {
            get { return m_wordsToCheck.Count != 0; } 
        }

        public string GetNextWord()
        {
            return m_wordsToCheck.Dequeue();
        }

        public Int32 FriendsCount
        {
            get { return m_usedWords.Count; }
        }

        #region Fields

        private readonly HashSet<String> m_usedWords;
        private readonly Queue<String> m_wordsToCheck;

        #endregion
    }

    internal class Finder
    {
        public Finder()
        {
            m_head = new Node();
        }

        public void AddWord(String word)
        {
            Node node = m_head;

            for (int i = 0; i < word.Length; ++i)
            {
                node = node.GetChild(word[i]);
            }

#if DEBUG
            if (node.Word != null)
            {
                Console.WriteLine("{0} already in dictionayr", word);
            }
#endif
            node.Word = word;
        }

        private List<String> GetWords(string word)
        {
            return null;
        }

        private class Node
        {
            public Node()
            {
                m_childs = new Dictionary<char, Node>();
                m_word = null;
            }

            public Boolean ContainWord
            {
                get { return m_word != null; }
            }

            public String Word
            {
                get { return m_word; }
                set { m_word = value; }
            }

            public Node GetChild(char symbol)
            {
                // XXX double lookup
                if (m_childs.ContainsKey(symbol))
                {
                    return m_childs[symbol];
                }

                return (m_childs[symbol] = new Node());
            }

            #region Node Fields

            private Dictionary<char, Node> m_childs;
            private String m_word;

            #endregion
        }

        #region Fields 

        private Node m_head;

        #endregion
    }

    class Program
    {
        static int Main(string[] args)
        {
            if (args.Count() != 1)
            {
                return 1;
            }

            List<String> testCases = new List<string>();
            Finder finder = new Finder();
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
                    // add to vocabulary
                    finder.AddWord(line);
                }
            }

            foreach (string testCase in testCases)
            {
            }

            return 0;
        }
    }
}
