using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace tree_cs
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
                }

                foreach (string testCase in testCases)
                {
                }
            }
        }
    }
}
