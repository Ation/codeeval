using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace tree_cs
{
    internal class NetworkMap
    {
        public NetworkMap()
        {
        }

        public void AddWord(String word)
        {
        }

        public int GetNetworkSize(String word)
        {
        }
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
