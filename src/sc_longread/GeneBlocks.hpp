#include <vector>
#include <string>
#include <map>
#include <set>

class GeneBlocks
{
  /*
    a class for storing info about individual gene blocks
    can be updated with add_gene
  */
  public:
    GeneBlocks(int start, int end, std::vector<std::string> transcript_list, std::string a_gene);
    
    int start, end;
    std::vector<std::string> 
    transcript_list;
    std::map<std::string, std::vector<std::string>>
    gene_to_transcript;
    std::map<std::string, std::vector<std::string>>
    gene_to_tr;

    void add_gene(int start, int end, std::vector<std::string> transcript_list, std::string a_gene);
};

GeneBlocks::GeneBlocks (int start, int end, std::vector<std::string> transcript_list, std::string a_gene)
{
  /* 
    initializes all of the object properties 
  */
 
  this->start = start; this->end = end;
  this->transcript_list = transcript_list;
  this->gene_to_transcript[a_gene] = transcript_list;
}

void 
GeneBlocks::add_gene(int start, int end, std::vector<std::string> transcript_list, std::string a_gene)
{
  /*
    takes a new gene (with a transcript list and a gene name)
    and adds it to the GeneBlocks object
  */

  // update the end pos if necessary
  this->end = std::max(this->end, end);
  
  // import everything from the new transcript_list
  for (const auto & i : transcript_list)
  {
    this->transcript_list.push_back(i);
  }

  // add the new transcript_list to the gene_to_transcript dictionary
  this->gene_to_transcript[a_gene] = transcript_list;
}