// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// parse_json_config_cpp
Rcpp::List parse_json_config_cpp(std::string jsonFile);
RcppExport SEXP _FLAMES_parse_json_config_cpp(SEXP jsonFileSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type jsonFile(jsonFileSEXP);
    rcpp_result_gen = Rcpp::wrap(parse_json_config_cpp(jsonFile));
    return rcpp_result_gen;
END_RCPP
}
// print_config_cpp
void print_config_cpp(Rcpp::List config);
RcppExport SEXP _FLAMES_print_config_cpp(SEXP configSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type config(configSEXP);
    print_config_cpp(config);
    return R_NilValue;
END_RCPP
}
// gtf_to_bed_cpp
void gtf_to_bed_cpp(std::string in_gtf, std::string out_bed, std::string chrom_sizes_file);
RcppExport SEXP _FLAMES_gtf_to_bed_cpp(SEXP in_gtfSEXP, SEXP out_bedSEXP, SEXP chrom_sizes_fileSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type in_gtf(in_gtfSEXP);
    Rcpp::traits::input_parameter< std::string >::type out_bed(out_bedSEXP);
    Rcpp::traits::input_parameter< std::string >::type chrom_sizes_file(chrom_sizes_fileSEXP);
    gtf_to_bed_cpp(in_gtf, out_bed, chrom_sizes_file);
    return R_NilValue;
END_RCPP
}
// read_entire_bam_cpp
void read_entire_bam_cpp(std::string bam_in, std::string log_out);
RcppExport SEXP _FLAMES_read_entire_bam_cpp(SEXP bam_inSEXP, SEXP log_outSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type bam_in(bam_inSEXP);
    Rcpp::traits::input_parameter< std::string >::type log_out(log_outSEXP);
    read_entire_bam_cpp(bam_in, log_out);
    return R_NilValue;
END_RCPP
}
// find_isoform_cpp
Rcpp::List find_isoform_cpp(std::string gff3, std::string genome_bam, std::string isoform_gff3, std::string tss_test_stat, std::string genomefa, std::string transcript_fa, int downsample_ratio, Rcpp::List config_list, std::string raw_splice_isoform);
RcppExport SEXP _FLAMES_find_isoform_cpp(SEXP gff3SEXP, SEXP genome_bamSEXP, SEXP isoform_gff3SEXP, SEXP tss_test_statSEXP, SEXP genomefaSEXP, SEXP transcript_faSEXP, SEXP downsample_ratioSEXP, SEXP config_listSEXP, SEXP raw_splice_isoformSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type gff3(gff3SEXP);
    Rcpp::traits::input_parameter< std::string >::type genome_bam(genome_bamSEXP);
    Rcpp::traits::input_parameter< std::string >::type isoform_gff3(isoform_gff3SEXP);
    Rcpp::traits::input_parameter< std::string >::type tss_test_stat(tss_test_statSEXP);
    Rcpp::traits::input_parameter< std::string >::type genomefa(genomefaSEXP);
    Rcpp::traits::input_parameter< std::string >::type transcript_fa(transcript_faSEXP);
    Rcpp::traits::input_parameter< int >::type downsample_ratio(downsample_ratioSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type config_list(config_listSEXP);
    Rcpp::traits::input_parameter< std::string >::type raw_splice_isoform(raw_splice_isoformSEXP);
    rcpp_result_gen = Rcpp::wrap(find_isoform_cpp(gff3, genome_bam, isoform_gff3, tss_test_stat, genomefa, transcript_fa, downsample_ratio, config_list, raw_splice_isoform));
    return rcpp_result_gen;
END_RCPP
}
// match_cell_barcode_cpp
void match_cell_barcode_cpp(Rcpp::String fastq_dir, Rcpp::String stats_file, Rcpp::String out_fastq, Rcpp::String ref_csv, int MAX_DIST, int UMI_LEN);
RcppExport SEXP _FLAMES_match_cell_barcode_cpp(SEXP fastq_dirSEXP, SEXP stats_fileSEXP, SEXP out_fastqSEXP, SEXP ref_csvSEXP, SEXP MAX_DISTSEXP, SEXP UMI_LENSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type fastq_dir(fastq_dirSEXP);
    Rcpp::traits::input_parameter< Rcpp::String >::type stats_file(stats_fileSEXP);
    Rcpp::traits::input_parameter< Rcpp::String >::type out_fastq(out_fastqSEXP);
    Rcpp::traits::input_parameter< Rcpp::String >::type ref_csv(ref_csvSEXP);
    Rcpp::traits::input_parameter< int >::type MAX_DIST(MAX_DISTSEXP);
    Rcpp::traits::input_parameter< int >::type UMI_LEN(UMI_LENSEXP);
    match_cell_barcode_cpp(fastq_dir, stats_file, out_fastq, ref_csv, MAX_DIST, UMI_LEN);
    return R_NilValue;
END_RCPP
}
// merge_bulk_fastq_cpp
void merge_bulk_fastq_cpp(Rcpp::StringVector fastq_files, Rcpp::String out_fastq);
RcppExport SEXP _FLAMES_merge_bulk_fastq_cpp(SEXP fastq_filesSEXP, SEXP out_fastqSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type fastq_files(fastq_filesSEXP);
    Rcpp::traits::input_parameter< Rcpp::String >::type out_fastq(out_fastqSEXP);
    merge_bulk_fastq_cpp(fastq_files, out_fastq);
    return R_NilValue;
END_RCPP
}
// quantification_cpp
void quantification_cpp(Rcpp::List config_list, std::string realign_bam, std::string transcript_fa_idx, Rcpp::List isoform_objects_list, std::string tr_cnt_csv, std::string tr_badcov_cnt_csv, std::string isoform_gff3, std::string annot, std::string isoform_gff3_f, std::string FSM_anno_out);
RcppExport SEXP _FLAMES_quantification_cpp(SEXP config_listSEXP, SEXP realign_bamSEXP, SEXP transcript_fa_idxSEXP, SEXP isoform_objects_listSEXP, SEXP tr_cnt_csvSEXP, SEXP tr_badcov_cnt_csvSEXP, SEXP isoform_gff3SEXP, SEXP annotSEXP, SEXP isoform_gff3_fSEXP, SEXP FSM_anno_outSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type config_list(config_listSEXP);
    Rcpp::traits::input_parameter< std::string >::type realign_bam(realign_bamSEXP);
    Rcpp::traits::input_parameter< std::string >::type transcript_fa_idx(transcript_fa_idxSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type isoform_objects_list(isoform_objects_listSEXP);
    Rcpp::traits::input_parameter< std::string >::type tr_cnt_csv(tr_cnt_csvSEXP);
    Rcpp::traits::input_parameter< std::string >::type tr_badcov_cnt_csv(tr_badcov_cnt_csvSEXP);
    Rcpp::traits::input_parameter< std::string >::type isoform_gff3(isoform_gff3SEXP);
    Rcpp::traits::input_parameter< std::string >::type annot(annotSEXP);
    Rcpp::traits::input_parameter< std::string >::type isoform_gff3_f(isoform_gff3_fSEXP);
    Rcpp::traits::input_parameter< std::string >::type FSM_anno_out(FSM_anno_outSEXP);
    quantification_cpp(config_list, realign_bam, transcript_fa_idx, isoform_objects_list, tr_cnt_csv, tr_badcov_cnt_csv, isoform_gff3, annot, isoform_gff3_f, FSM_anno_out);
    return R_NilValue;
END_RCPP
}
// minimap2_align_cpp
void minimap2_align_cpp(std::string mm2_prog_path, std::string fa_file, std::string fq_in, std::string sam_out, bool no_flank, std::string bed12_junc);
RcppExport SEXP _FLAMES_minimap2_align_cpp(SEXP mm2_prog_pathSEXP, SEXP fa_fileSEXP, SEXP fq_inSEXP, SEXP sam_outSEXP, SEXP no_flankSEXP, SEXP bed12_juncSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type mm2_prog_path(mm2_prog_pathSEXP);
    Rcpp::traits::input_parameter< std::string >::type fa_file(fa_fileSEXP);
    Rcpp::traits::input_parameter< std::string >::type fq_in(fq_inSEXP);
    Rcpp::traits::input_parameter< std::string >::type sam_out(sam_outSEXP);
    Rcpp::traits::input_parameter< bool >::type no_flank(no_flankSEXP);
    Rcpp::traits::input_parameter< std::string >::type bed12_junc(bed12_juncSEXP);
    minimap2_align_cpp(mm2_prog_path, fa_file, fq_in, sam_out, no_flank, bed12_junc);
    return R_NilValue;
END_RCPP
}
// minimap2_tr_align_cpp
void minimap2_tr_align_cpp(std::string mm2_prog_path, std::string fa_file, std::string fq_in, std::string sam_out);
RcppExport SEXP _FLAMES_minimap2_tr_align_cpp(SEXP mm2_prog_pathSEXP, SEXP fa_fileSEXP, SEXP fq_inSEXP, SEXP sam_outSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type mm2_prog_path(mm2_prog_pathSEXP);
    Rcpp::traits::input_parameter< std::string >::type fa_file(fa_fileSEXP);
    Rcpp::traits::input_parameter< std::string >::type fq_in(fq_inSEXP);
    Rcpp::traits::input_parameter< std::string >::type sam_out(sam_outSEXP);
    minimap2_tr_align_cpp(mm2_prog_path, fa_file, fq_in, sam_out);
    return R_NilValue;
END_RCPP
}
// what2
void what2();
RcppExport SEXP _FLAMES_what2() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    what2();
    return R_NilValue;
END_RCPP
}
// what
void what();
RcppExport SEXP _FLAMES_what() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    what();
    return R_NilValue;
END_RCPP
}

RcppExport SEXP run_testthat_tests(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"_FLAMES_parse_json_config_cpp", (DL_FUNC) &_FLAMES_parse_json_config_cpp, 1},
    {"_FLAMES_print_config_cpp", (DL_FUNC) &_FLAMES_print_config_cpp, 1},
    {"_FLAMES_gtf_to_bed_cpp", (DL_FUNC) &_FLAMES_gtf_to_bed_cpp, 3},
    {"_FLAMES_read_entire_bam_cpp", (DL_FUNC) &_FLAMES_read_entire_bam_cpp, 2},
    {"_FLAMES_find_isoform_cpp", (DL_FUNC) &_FLAMES_find_isoform_cpp, 9},
    {"_FLAMES_match_cell_barcode_cpp", (DL_FUNC) &_FLAMES_match_cell_barcode_cpp, 6},
    {"_FLAMES_merge_bulk_fastq_cpp", (DL_FUNC) &_FLAMES_merge_bulk_fastq_cpp, 2},
    {"_FLAMES_quantification_cpp", (DL_FUNC) &_FLAMES_quantification_cpp, 10},
    {"_FLAMES_minimap2_align_cpp", (DL_FUNC) &_FLAMES_minimap2_align_cpp, 6},
    {"_FLAMES_minimap2_tr_align_cpp", (DL_FUNC) &_FLAMES_minimap2_tr_align_cpp, 4},
    {"_FLAMES_what2", (DL_FUNC) &_FLAMES_what2, 0},
    {"_FLAMES_what", (DL_FUNC) &_FLAMES_what, 0},
    {"run_testthat_tests", (DL_FUNC) &run_testthat_tests, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_FLAMES(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
