#include "parse_realigned_bam.hpp"

std::unordered_map<std::string, int>
file_to_map(std::string filename)
{
    /* 
        parse a file into a map. the file should look like:
            text 10
            word 4
            dhgukrahgk 10
    */
    std::unordered_map<std::string, int>
    map;

    std::ifstream
    file(filename);

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream
        linestream (line);

        // break each line into words
        std::vector<std::string> words;
        std::string word;
        while (std::getline(linestream, word, ' ')) {
            words.push_back(word);
        }

        map[words[0]] = atoi(words[1].c_str());
    }

    return map;
}

// [[Rcpp::export]]
void
read_entire_bam
(
    std::string bam_in
)
{
    // read a bamfile
    bamFile bam = bam_open(bam_in.c_str(), "r"); // bam.h
    bam_index_t *bam_index = bam_index_load(bam_in.c_str());
    bam_header_t *header = bam_header_read(bam); // bam.h

    bam1_t *b = bam_init1();

    while (bam_read1(bam, b) >= 0) {
        std::cout << b->core.tid << ", " << b->core.pos << "\n";
    }
    bam_close(bam);
}

void
parse_realigned_bam
(
    std::string bam_in,
    std::string fa_idx_f,
    std::string min_sup_reads,
    std::string min_tr_coverage,
    std::string min_read_coverage,
    std::unordered_map<std::string, std::string> kwargs
)
{
    // we need to read in the fa_idx_f file line by line, adding each one to the dict
    std::unordered_map<std::string, int>
    fa_idx = file_to_map(fa_idx_f);

    std::unordered_map<std::string, std::string>
    bc_tr_count_dict = {};

    std::unordered_map<std::string, std::string>
    bc_tr_badvoc_count_dict = {};

    std::unordered_map<std::string, std::string>
    tr_cov_dict = {};
    
    std::unordered_map<std::string, int>
    count_stat = {};

    // read a bamfile
    bamFile bam = bam_open(bam_in.c_str(), "r"); // bam.h
    bam_index_t *bam_index = bam_index_load(bam_in.c_str());
    bam_header_t *header = bam_header_read(bam); // bam.h

    bam1_t *b = bam_init1();
    while (bam_read1(bam, b) >= 0) {
        std::cout << b->core.tid << ", " << b->core.pos << "\n";
    }
    bam_close(bam);

    std::unordered_map<std::string, std::string>
    bc_dict;
    if (kwargs.count("bc_file") > 0) {
        bc_dict = make_bc_dict(kwargs["bc_file"]);
    }

    
    // produce and populate a records file
    std::vector<Record>
    records = {};
    // bam_fetch(bam, bam_index, tid, block.start, block.end, &records, fetch_function);
}



std::unordered_map<std::string, std::string>
make_bc_dict(std::string bc_anno)
{
    /*  
        opens a bc file, parses it into a dictionary format
    */

    // open the file
    std::ifstream
    bc_file (bc_anno);

    // make a dictionary to output to
    std::unordered_map<std::string, std::string>
    bc_dict;

    // now parse the file line by line
    std::string line;
    bool header_line = true;
    while (std::getline(bc_file, line)) {
        // skip the first line
        if (header_line) {
            header_line = false;
            continue;
        }

        std::stringstream
        linestream (line);

        // break each line into words
        std::vector<std::string> words;
        std::string word;
        while (std::getline(linestream, word, ' ')) {
            words.push_back(word);
        }

        bc_dict[words[1]] = words[0];
    }

    return bc_dict;
}