Solution to "Levenshtein Distance" challange
https://www.codeeval.com/open_challenges/58/

TODO:
    for C++ solution
        decrease memory consuption
            use char* instead of string without zero symbol
            use prefix for words
        test with "prefix tree"

        time
            there could be some duplicates in test cases

Results:
    separate sets for different lenght did not work out (not memory/speed improvements)

    try with prefix reduction in unordered set no improvements