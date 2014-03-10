using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

// Current solution is not working because networks are not merging when word is added
// so to make it work node should search for all existing networks that are welcome for this
// word and merge them on joining

// TODO: join networks
// TODO: add 1 to network if word is not in a vocabulary

namespace tree_cs
{
    internal class FriendsNetwork
    {
        public FriendsNetwork()
        {
            FriendsCount = 0;
        }

        public void AddFriendToNetwork()
        {
            FriendsCount++;
        }

        public void JoinNetwork(FriendsNetwork friendNet)
        {
            FriendsCount += friendNet.FriendsCount;
            friendNet.FriendsCount = FriendsCount;
        }

        public int FriendsCount { get; private set; }
    }

    class Node
    {
        public Node(char symbol)
        {
            m_childs = new Dictionary<char, Node>();
            Network = null;
            m_word = null;
            m_symbol = symbol;
        }

        public FriendsNetwork GetWordNetwork(string word)
        {
            Node currentNode = this;
            Node stepNode;
            FriendsNetwork result = null;

            for (int i = 0; (i < word.Length) && (currentNode != null); i++)
            {
                // insert
                foreach (var childPair in currentNode.m_childs)
                {
                    stepNode = currentNode;

                    for (var j = i; (j < word.Length) && (stepNode != null); j++)
                    {
                        stepNode = stepNode.GetChild(word[j]);
                    }

                    if ((stepNode != null) && (stepNode.Network != null))
                    {
                        result = stepNode.Network;
                        break;
                    }
                }

                if (result != null)
                {
                    break;
                }

                // replace
                foreach (var childPair in currentNode.m_childs)
                {
                    stepNode = currentNode;

                    for (var j = i + 1; (j < word.Length) && (stepNode != null); j++)
                    {
                        stepNode = stepNode.GetChild(word[j]);
                    }

                    if ((stepNode != null) && (stepNode.Network != null))
                    {
                        result = stepNode.Network;
                        break;
                    }
                }

                if (result != null)
                {
                    break;
                }

                // skip
                stepNode = currentNode;
                for (int j = i + 1; (j < word.Length) && (stepNode != null); j++)
                {
                    stepNode = stepNode.GetChild(word[j]);
                }

                currentNode = currentNode.GetChild(word[i]);
            }

            return result;
        }

        public void AddWord(String word)
        {
            var route = new List<Node>(word.Length + 1);
            FriendsNetwork net = null;

            Node currentNode = this;
            // adding the world and saving the route
            for (int i = 0; i < word.Length; i++)
            {
                route.Add(currentNode);
                currentNode = currentNode.GetOrCreateChild(word[i]);
            }

            currentNode.m_word = word;
            route.Add(currentNode);

            // try to find existing network
            for (int i = word.Length; i >= 0; i--)
            {
                // insertions
                foreach (var child in route[i].m_childs)
                {
                    currentNode = child.Value;
                    for (int j = i; (j < word.Length) && (currentNode != null); j++)
                    {
                        currentNode = currentNode.GetChild(word[j]);
                    }

                    if ((currentNode != null) && (currentNode.Network != null))
                    {
                        net = currentNode.Network;
                        break;
                    }
                }

                if (net != null)
                {
                    break;
                }

                //replacement
                foreach (var child in route[i].m_childs)
                {
                    currentNode = child.Value;
                    for (int j = i+1; (j < word.Length) && (currentNode != null); j++)
                    {
                        currentNode = currentNode.GetChild(word[j]);
                    }

                    if ((currentNode != null) && (currentNode.Network != null))
                    {
                        net = currentNode.Network;
                        break;
                    }
                }

                if (net != null)
                {
                    break;
                }

                //removals
                currentNode = route[i];
                for (int j = i + 1; (j < word.Length) && (currentNode != null); j++)
                {
                    currentNode = currentNode.GetChild(word[j]);
                }

                if ((currentNode != null) && (currentNode.Network != null))
                {
                    net = currentNode.Network;
                    break;
                }
            }

            route[word.Length].EnterNetwork(net ?? new FriendsNetwork());
        }

        private Node GetChild(char symbol)
        {
            Node result;
            if (m_childs.TryGetValue(symbol, out result))
            {
                return result;
            }

            return null;
        }

        private Node  GetOrCreateChild(char symbol)
        {
            Node node;
            if (!m_childs.TryGetValue(symbol, out node))
            {
                node = new Node(symbol);
                m_childs.Add(symbol, node);
            }

            return node;
        }

        private void EnterNetwork(FriendsNetwork net)
        {
#if DEBUG
            if (Network != null)
            {
                Console.WriteLine("Node contain network");
            }
#endif
            Network = net;
            Network.AddFriendToNetwork();
        }

        public FriendsNetwork Network { get; private set; }

        private Dictionary<char, Node> m_childs;
        private string m_word;
        private char m_symbol;
    }

    internal class NetworkMap
    {
        public NetworkMap()
        {
            m_head = new Node('0');
        }

        public void AddWord(String word)
        {
            m_head.AddWord(word);
        }

        public int GetNetworkSize(String word)
        {
            var network = m_head.GetWordNetwork(word);

            return (network == null ? 1 : network.FriendsCount);
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
