#ifndef FASTA_READER_H
#define FASTA_READER_H

#include <string>
#include <vector>
#include <fstream>
#include "exceptions.h"
#include "node.h"
//#include "settings.h"
#include "utils/fasta_entry.h"

using namespace std;

namespace ppa
{

class Fasta_reader
{
    unsigned int chars_by_line;
    float dna_pi[4];

    void rna_to_DNA(string *sequence) const;

public:
    Fasta_reader() : chars_by_line(60) {}

    void set_chars_by_line(int n) { chars_by_line = n; }

    void read(istream & input, vector<Fasta_entry> & seqs, bool short_names) const throw (Exception);
    void read(const string & path, vector<Fasta_entry> & seqs, bool short_names) const throw (Exception)
    {
        ifstream input(path.c_str(), ios::in);
        read(input, seqs, short_names);
        input.close();
    }
    void read_fasta(istream & input, vector<Fasta_entry> & seqs, bool short_names) const throw (Exception);
    void read_fastq(istream & input, vector<Fasta_entry> & seqs) const throw (Exception);
    void read_graph(istream & input, vector<Fasta_entry> & seqs, bool short_names) const throw (Exception);

    void trim_fastq_reads(vector<Fasta_entry> * seqs) const throw (Exception);

    void write(ostream & output, const vector<Fasta_entry> & seqs) const throw (Exception);
    void write(const string & path, const vector<Fasta_entry> & seqs, bool overwrite=true) const throw (Exception)
    {
        ofstream output( (path+".fas").c_str(), overwrite ? (ios::out) : (ios::out|ios::app));
        write(output, seqs);
        output.close();
    }

    void write_fastq(ostream & output, const vector<Fasta_entry> & seqs) const throw (Exception);
    void write_fastq(const string & path, const vector<Fasta_entry> & seqs, bool overwrite=true) const throw (Exception)
    {
        ofstream output( (path+".fastq").c_str(), overwrite ? (ios::out) : (ios::out|ios::app));
        write_fastq(output, seqs);
        output.close();
    }

    void write_anctree(const string outfile, Node *root, bool overwrite=true)
    {
        ofstream output( (outfile+".anctree").c_str(), overwrite ? (ios::out) : (ios::out|ios::app));
        if (! output) { throw IOException ("Fasta_reader::write_anctree. Failed to open file"); }

        output<<root->print_tree(true);
        output.close();
    }

    void write_graph(ostream & output, Node * root) const throw (Exception);
    void write_graph(const string & path, Node * root, bool overwrite=true) const throw (Exception)
    {
        ofstream output( (path+".grp").c_str(), overwrite ? (ios::out) : (ios::out|ios::app));
        write_graph(output, root);
        output.close();
    }


    bool check_alphabet(string alphabet, string full_alphabet, vector<Fasta_entry> & seqs)  throw (Exception);
//    void check_sequence_names(const vector<Fasta_entry> *sequences,const vector<Node*> *leaf_nodes, const Settings *st) const;
    bool check_sequence_names(const vector<Fasta_entry> *sequences,const vector<Node*> *leaf_nodes) const;

    float* base_frequencies() { return dna_pi; }
    int check_sequence_data_type(const vector<Fasta_entry> & seqs);

    void place_sequences_to_nodes(const vector<Fasta_entry> *sequences,vector<Node*> *leaf_nodes, string full_char_alphabet, bool gapped = false);
};
}

#endif // FASTA_READER_H

