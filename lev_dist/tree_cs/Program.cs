using System;
using System.Collections.Generic;
using System.IO;

namespace tree_cs
{
    internal class NetworkMap
    {
        private class Node
        {
            public Node()
            {
                m_nodes = new Dictionary<char, Node>();
                m_word = null;
            }

            public string GetWord()
            {
                return m_word;
            }

            public void SetWord(string word)
            {
#if DEBUG
                if (m_word != null)
                {
                    Console.WriteLine("ERROR: allready have a word: {0} - {1}", m_word, word);
                }
#endif
                m_word = word;
            }

            public Node GetOrCreateNode(char symbol)
            {
                Node result;
                if (!m_nodes.TryGetValue(symbol, out result))
                {
                    result = new Node();
                    m_nodes.Add(symbol, result);
                }

                return result;
            }

            public Node GetNode(char symbol)
            {
                Node result;
                if (m_nodes.TryGetValue(symbol, out result))
                {
                    return result;
                }

                return null;
            }

            public Dictionary<char, Node> GetChilds()
            {
                return m_nodes;
            }

            private Dictionary<char, Node> m_nodes;
            private string m_word;
        }

        public NetworkMap()
        {
            m_rootNode = new Node();
        }

        public void AddWord(String word)
        {
            var node = m_rootNode;

            for (int i = 0; i < word.Length; i++)
            {
                node = node.GetOrCreateNode(word[i]);
            }

            node.SetWord(word);
        }

        public int GetNetworkSize(String word)
        {
            var wordsToCheck = new LinkedList<string>();
            var usedWords = new HashSet<string>();

            wordsToCheck.AddFirst(word);
            usedWords.Add(word);

            while (wordsToCheck.Count != 0)
            {
                var friendWord = wordsToCheck.First.Value;
                wordsToCheck.RemoveFirst();

                var node = m_rootNode;
                Node currentNode;
                int i = 0;

                while (node != null)
                {
                    foreach (var childNode in node.GetChilds().Values)
                    {
                        //insert
                        currentNode = childNode;

                        for (int j = i; (j < friendWord.Length) && (currentNode != null); j++)
                        {
                            currentNode = currentNode.GetNode(friendWord[j]);
                        }

                        if (currentNode != null)
                        {
                            var nodeWord = currentNode.GetWord();
                            if ((nodeWord != null) && (!usedWords.Contains(nodeWord)))
                            {
                                wordsToCheck.AddLast(nodeWord);
                            }
                        }

                        //replace
                        currentNode = childNode;

                        for (int j = i + 1; (j < friendWord.Length) && (currentNode != null); j++)
                        {
                            currentNode = currentNode.GetNode(friendWord[j]);
                        }

                        if (currentNode != null)
                        {
                            var nodeWord = currentNode.GetWord();
                            if ((nodeWord != null) && (!usedWords.Contains(nodeWord)))
                            {
                                wordsToCheck.AddLast(nodeWord);
                            }
                        }
                    }

                    //skip
                    currentNode = node;
                    for (int j = i + 1; (j < friendWord.Length) && (currentNode != null); j++)
                    {
                        currentNode = currentNode.GetNode(friendWord[j]);
                    }
                    if (currentNode != null)
                    {
                        var nodeWord = currentNode.GetWord();
                        if ((nodeWord != null) && (!usedWords.Contains(nodeWord)))
                        {
                            wordsToCheck.AddLast(nodeWord);
                        }
                    }

                    if (i == friendWord.Length)
                    {
                        break;
                    }

                    node = node.GetNode(friendWord[i]);
                    i++;
                }

                if (node != null)
                {
                    string nodeWord = node.GetWord();
                    if (nodeWord != null)
                    {
                        usedWords.Add(nodeWord);
                    }
                }
            }

            return usedWords.Count;
        }

        private Node m_rootNode;
    }

    class Program
    {
        static int Main(string[] args)
        {
            if (args.Length != 1)
            {
                return 1;
            }

            var testCases = new List<string>();
            var networkMap = new NetworkMap();
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
                    networkMap.AddWord(line);
                }
            }


            foreach (string testCase in testCases)
            {
                Console.WriteLine(networkMap.GetNetworkSize(testCase));
            }

            return 0;
        }
    }
}
