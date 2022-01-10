#include "annotate_filter_gff.h"

void
annotate_full_splice_match
(
    std::unordered_map<std::string, std::vector<StartEndPair>>
    transcript_to_exon,

    std::unordered_map<std::string, std::vector<StartEndPair>>
    transcript_to_exon_ref,

    std::unordered_map<std::string, Pos>
    transcript_dict,

    std::unordered_map<std::string, Pos>
    transcript_dict_ref,

    std::string
    anno_out,

    std::unordered_map<std::string, int>
    tr_count,

    int
    min_sup_reads
)
{
    std::unordered_map<std::string, std::vector<std::string>>
    splice_dict = {};

    std::unordered_map<std::string, std::vector<std::string>>
    splice_dict_ref = {};

    std::unordered_map<std::string, std::vector<std::string>>
    splice_gene_dict = {};

    std::vector<std::string>
    tr_id_list;

    std::vector<std::string>
    FSM_id_list;

    std::vector<bool>
    FSM_to_reference;

    std::vector<std::string>
    gene_id_list;

    for (const auto & [tr, exon_list] : transcript_to_exon) {
        std::vector<int>
        tmp;

        for (const auto & exon : exon_list) {
            tmp.push_back(exon.start);
            tmp.push_back(exon.end);
        }

        // skip if the transcript only has one exon
        if (tmp.size() == 2) {
            continue;
        }

        auto
        tmp_slice = std::vector<int>(tmp.begin() + 1, tmp.end() - 1);

        if (tr_count.count(tr) && tr_count[tr] >= min_sup_reads) {
            if (splice_dict.count(tr) == 0) {
                splice_dict[tr] = {};
            }
            splice_dict[tr].push_back(tr);

            if (splice_gene_dict.count(tr) == 0) {
                splice_gene_dict[tr] = {};
            }
            splice_gene_dict[tr].push_back(transcript_dict[tr].parent_id);
        }
    }

    for (const auto & [tr, exon_list] : transcript_to_exon_ref) {
        std::vector<int>
        tmp;

        for (const auto & exon : exon_list) {
            tmp.push_back(exon.start);
            tmp.push_back(exon.end);
        }
        
        // skip if the reference transcript only has one exon
        if (tmp.size() == 2) {
            continue;
        }

        auto
        tmp_slice = std::vector<int>(tmp.begin() + 1, tmp.end() - 1);

        if (tr_count.count(tr) > 0 && transcript_to_exon.count(tr) == 0 && tr_count[tr] >= min_sup_reads) {
            if (splice_dict.count(tr) == 0) {
                splice_dict[tr] = {};
            }
            splice_dict[tr].push_back(tr);

            if (splice_gene_dict.count(tr) == 0) {
                splice_gene_dict[tr] = {};
            }
       if (splice_dict.count(tr) == 0) {
                splice_dict[tr] = {};
            }
            splice_dict[tr].push_back(tr);
            splice_gene_dict[tr].push_back(transcript_dict_ref[tr].parent_id);
        }

        if (splice_dict_ref.count(tr) == 0) {
            splice_dict_ref[tr] = {};
        }
        splice_dict_ref[tr].push_back(tr);
    }

    for (const auto & [key, val] : splice_gene_dict) {
        // get all the unique values
        std::set<std::string>
        dict_set;
        for (const auto & i : val) {
            dict_set.insert(i);
        }

        if (dict_set.size() > 1) {
            std::cout << "Shared splice chain: (";
            for (const auto & i : dict_set) {
                std::cout << i << " ";
            }
        }
        std::cout << "), " << key;
    }

    for (const auto & [key, val] : splice_dict) {
        if (key.size() == 1) {
            tr_id_list.push_back(val.front());
            gene_id_list.push_back(splice_gene_dict[key].front());
            if (splice_dict_ref.count(key) > 0) {
                FSM_id_list.push_back(splice_dict_ref[key].front());
                FSM_to_reference.push_back(true);
            } else {
                FSM_id_list.push_back(val.front());
                FSM_to_reference.push_back(false);
            }
        } else {
            std::vector<std::string>
            ref_tr;
            for (const auto & tr : val) {
                if (transcript_to_exon_ref.count(tr) > 0) {
                    ref_tr.push_back(tr);
                }
            }

            if (ref_tr.size() > 0) {
                for (const auto & tr : val) {
                    tr_id_list.push_back(tr);
                    gene_id_list.push_back(val.front());
                    FSM_id_list.push_back(ref_tr.front());
                    FSM_to_reference.push_back(true);
                }
            } else if (splice_dict_ref.count(key) > 0) {
                for (const auto & tr : val) {
                    tr_id_list.push_back(tr);
                    gene_id_list.push_back(val.front());
                    FSM_id_list.push_back(val.front());
                    FSM_to_reference.push_back(true);
                }
            } else {
                for (const auto & tr : val) {
                    tr_id_list.push_back(tr);
                    gene_id_list.push_back(val.front());
                    FSM_id_list.push_back(val.front());
                    FSM_to_reference.push_back(false);
                }
            }
        }
    }

    std::ofstream
    anno (anno_out);

    anno << "transcript_id,gene_id,FSM_match,FSM_match_to_ref,total_count\n";
    for (int i = 0; i < tr_id_list.size(); ++i) {
        anno << tr_id_list[i] << ","
            << gene_id_list[i] << ","
            << FSM_id_list[i] << ","
            << FSM_to_reference[i] << ","
            << tr_count[tr_id_list[i]];
    }
}

void
annotate_filter_gff
(
    std::string isoform_gff,
    std::string ref_gff,
    std::string isoform_out,
    std::string anno_out,
    std::unordered_map<std::string, int> tr_count,
    int min_sup_reads,
    bool verbose
)
{
    /*
        combine FLAMES output with reference, 
        and filter out transcript by realignment result
    */

    GeneAnnoParser * geneAnnoParser = new GeneAnnoParser(isoform_gff);
    GFFData isoform_data = geneAnnoParser->parse();
    log_gff_data(isoform_data, "before_ann_cpp.gff");

    auto chr_to_gene = isoform_data.chr_to_gene;
    auto transcript_dict = isoform_data.transcript_dict;
    auto gene_to_transcript = isoform_data.gene_to_transcript;
    auto transcript_to_exon = isoform_data.transcript_to_exon;

    std::cout << "chr_to_gene.size():" << chr_to_gene.size() << "\n";
    std::cout << "transcript_dict.size():" << transcript_dict.size() << "\n";
    std::cout << "gene_to_transcript.size():" << gene_to_transcript.size() << "\n";
    std::cout << "transcript_to_exon.size():" << transcript_to_exon.size() << "\n";


    std::cout << "ref_gff:" << ref_gff << " (and we're reading it better)\n";
    geneAnnoParser = new GeneAnnoParser(ref_gff);
    GFFData ref_data = geneAnnoParser->parse();

    auto chr_to_gene_ref = ref_data.chr_to_gene;
    auto transcript_dict_ref = ref_data.transcript_dict;
    auto gene_to_transcript_ref = ref_data.gene_to_transcript;
    auto transcript_to_exon_ref = ref_data.transcript_to_exon;


    std::stringstream
    prt;
    prt << "\tFiltering and combining isoforms from realigned bam file:\n\tBefore filtering: " 
        << tr_count.size() << " isoforms in count matrix. "
        << transcript_to_exon_ref.size() << " isoforms in reference annotation. "
        << transcript_to_exon.size() << " isoforms in FLAMES raw output.\n";

    if (verbose) {
        std::cout << prt.str();
    }

    std::vector<std::string>
    gff_rec = {};

    int
    iso_rm = 0;
    int
    iso_kp = 0;

    for (const auto & [chr, gene_list] : chr_to_gene) {
        // populate new_gene_list with every gene from both the FLAMES output and the reference
        auto
        new_gene_list = gene_list;
        for (const auto & ref_gene : chr_to_gene_ref[chr]) {
            if (std::count(new_gene_list.begin(), new_gene_list.end(), ref_gene) == 0) {
                new_gene_list.push_back(ref_gene);
            }
        }

        for (const auto & gene : new_gene_list) {
            std::vector<std::string>
            gff_tmp;
            
            int
            total_cnt = 0,
            min = INT_MAX,
            max = INT_MIN;
            std::stringstream
            gff_line;

            if (gene_to_transcript.count(gene) > 0) {
                for (const auto & tr : gene_to_transcript[gene]) {
                    if (tr_count.count(tr) > 0 && tr_count[tr] >= min_sup_reads) {
                        gff_line = std::stringstream {};
                        gff_line << chr << "\t"
                                << "FLAMES" << "\t"
                                << "transcript" << "\t"
                                << transcript_to_exon[tr][0].start + 1 << "\t"
                                << transcript_to_exon[tr].back().end << "\t"
                                << "." << "\t"
                                << transcript_dict[tr].strand << "\t"
                                << "." << "\t"
                                << "ID="
                                    << "transcript:" << tr << ";"
                                    << "transcript_id:" << tr << ";"
                                << "Parent="
                                    << "gene:" << gene << ";"
                                << "support_count=" << tr_count[tr];
                        
                        gff_tmp.push_back(gff_line.str());

                        total_cnt += tr_count[tr];
                        min = std::min(min, transcript_to_exon[tr].front().start);
                        max = std::max(max, transcript_to_exon[tr].back().end);
                        int
                        exon_idx = 1;

                        for (const auto & exon : transcript_to_exon[tr]) {
                            gff_line = std::stringstream{};
                            gff_line << chr << "\t"
                                    << "FLAMES" << "\t"
                                    << "exon" << "\t"
                                    << exon.start + 1 << "\t" // +1 because gff is 1-based
                                    << exon.end << "\t"
                                    << "." << "\t"
                                    << transcript_dict[tr].strand << "\t"
                                    << "." << "\t"
                                    << "exon_id="
                                        << "exon:" << exon.start+1 << "_" << exon.end << ";"
                                    << "Parent="
                                        << "transcript:" << tr << ";"
                                    << "rank=" << exon_idx;
                            gff_tmp.push_back(gff_line.str());

                            exon_idx++;
                        }
                        iso_kp++;
                    } else {
                        iso_rm++;
                    }
                }
            }

            if (gene_to_transcript_ref.count(gene) > 0) {
                for (const auto & tr : gene_to_transcript_ref[gene]) {
                    if (transcript_dict.count(tr) == 0 && tr_count.count(tr) > 0 && tr_count[tr] >= min_sup_reads) {
                        // then it is not in FLAMES output but it is in tr_count
                        gff_line = std::stringstream {};
                        gff_line << chr << "\t"
                                << "reference" << "\t"
                                << "transcript" << "\t"
                                << transcript_to_exon_ref[tr][0].start + 1 << "\t"
                                << transcript_to_exon_ref[tr].back().end << "\t"
                                << "." << "\t"
                                << transcript_dict_ref[tr].strand << "\t"
                                << "." << "\t"
                                << "ID="
                                    << "transcript:" << tr << ";"
                                    << "transcript_id:" << tr << ";"
                                << "Parent="
                                    << "gene:" << gene << ";"
                                << "support_count=" << tr_count[tr];
                        gff_tmp.push_back(gff_line.str());

                        total_cnt += tr_count[tr];
                        min = std::min(min, transcript_to_exon_ref[tr].front().start);
                        max = std::max(max, transcript_to_exon_ref[tr].back().end);
                        int exon_idx = 1;
                        for (const auto & exon : transcript_to_exon_ref[tr]) {
                            gff_line = std::stringstream {};
                            gff_line << chr << "\t"
                                    << "reference" << "\t"
                                    << "exon" << "\t"
                                    << exon.start + 1 << "\t" // +1 because gff is 1-based
                                    << exon.end << "\t"
                                    << "." << "\t"
                                    << transcript_dict_ref[tr].strand << "\t"
                                    << "." << "\t"
                                    << "exon_id="
                                        << "exon:" << exon.start+1 << "_" << exon.end << ";"
                                    << "Parent="
                                        << "transcript:" << tr << ";"
                                    << "rank=" << exon_idx;
                            gff_tmp.push_back(gff_line.str());
                            exon_idx++;
                        }
                        iso_kp++;
                    }
                }
            }

            if (gff_tmp.size() > 0) {
                if (gene_to_transcript.count(gene) > 0) {
                    gff_line = std::stringstream {};
                    gff_line << chr << "\t"
                            << "FLAMES" << "\t"
                            << "gene" << "\t"
                            << min + 1 << "\t" // +1 because gff is 1-based
                            << max << "\t"
                            << "." << "\t"
                            << transcript_dict[gene_to_transcript[gene].front()].strand << "\t"
                            << "." << "\t"
                            << "ID="
                                << "gene:" << gene << ";"
                            << "gene_id=" << gene << ";"
                            << "support_count=" << total_cnt;
                    gff_tmp.insert(gff_tmp.begin(), gff_line.str());
                } else {
                    gff_line = std::stringstream {};
                    gff_line << chr << "\t"
                            << "FLAMES" << "\t"
                            << "gene" << "\t"
                            << min + 1 << "\t" // +1 because gff is 1-based
                            << max << "\t"
                            << "." << "\t"
                            << transcript_dict_ref[gene_to_transcript_ref[gene].front()].strand << "\t"
                            << "." << "\t"
                            << "ID="
                                << "gene:" << gene << ";"
                            << "gene_id=" << gene << ";"
                            << "support_count=" << total_cnt;
                    gff_tmp.insert(gff_tmp.begin(), gff_line.str());
                }

                for (const auto & entry : gff_tmp) {
                    gff_rec.push_back(entry);
                }
            }
        }
    }

    std::ofstream
    iso_annotated (isoform_out);

    iso_annotated << "##gff-version 3\n";
    for (const auto & entry : gff_rec) {
        iso_annotated << entry << "\n";
    }
    iso_annotated.close();

    prt = std::stringstream {};
    prt << "\tAfter filtering: "
        << "kept " << iso_kp << " isoforms. "
        << "removed " << iso_rm << " isoforms.\n";
    
    if (verbose) {
        std::cout << prt.str();
    }    
}