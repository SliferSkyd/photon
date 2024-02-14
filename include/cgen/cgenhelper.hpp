#ifndef __CGENHELPER_HPP__
#define __CGENHELPER_HPP__

#include <string>
#include <iostream>
#include <fstream>

namespace CgenHelper {
    const int MAX_INT = 100000000;
    const int WORD_SIZE = 4;
    const int LOG_WORD_SIZE = 2;

    const int EMPTYSLOT = 0;
    const std::string LABEL = ":\n";

    const std::string GLOBAL       = "\t.globl\t"; 
    const std::string ALIGN        = "\t.align\t2\n";
    const std::string WORD         = "\t.word\t";

    // register names,
    const std::string ZERO = "$zero";		// Zero register 
    const std::string ACC = "$a0";		// Accumulator 
    const std::string A1  = "$a1";		// For arguments to prim funcs 
    const std::string SELF= "$s0";		// Ptr to self (callee saves) 
    const std::string S1=   "$s1";		// Dont know what S1 does but it is used in cool generated code and it 
    // cannot be replaced by other regs
    const std::string T1  = "$t1";		// Temporary 1 
    const std::string T2  = "$t2";            // Temporary 2 
    const std::string T3  = "$t3";            // Temporary 3 
    const std::string SP  = "$sp";		// Stack pointer 
    const std::string FP  = "$fp";		// Frame pointer 
    const std::string RA  = "$ra";		// Return address

    // Opcodes
    const std::string JALR = "\tjalr\t";
    const std::string JAL  = "\tjal\t";               
    const std::string RET  = "\tjr\t" + RA + "\t";
    
    const std::string SW   = "\tsw\t";
    const std::string LW   = "\tlw\t";
    const std::string LI   = "\tli\t";
    const std::string LA   = "\tla\t";

    const std::string MOVE = "\tmove\t";
    const std::string NEG  = "\tneg\t";
    const std::string ADD  = "\tadd\t";
    const std::string ADDI = "\taddi\t";
    const std::string ADDU = "\taddu\t";
    const std::string ADDIU= "\taddiu\t";
    const std::string DIV  = "\tdiv\t";
    const std::string MUL  = "\tmul\t";
    const std::string SUB  = "\tsub\t";
    const std::string SLL  = "\tsll\t";
    const std::string BEQZ = "\tbeqz\t";
    const std::string BRANCH  = "\tb\t";
    const std::string BEQ     = "\tbeq\t";
    const std::string BNE     = "\tbne\t";
    const std::string BLEQ    = "\tble\t";
    const std::string BLT     = "\tblt\t";
    const std::string BGT     = "\tbgt\t";
    
    const std::string NOR     = "\tnor\t";

    const std::string SEQ     = "\tseq\t";
    const std::string SNE     = "\tsne\t";
    const std::string SGE     = "\tsge\t";
    const std::string SGT     = "\tsgt\t";
    const std::string SLE     = "\tsle\t";
    const std::string SLT     = "\tslt\t";

    int labelNum = 0;

    /** Returns a new label.
     * @return a new label
     * */
    int newLabel() {
        return labelNum++;
    }

    void setOutputDir(std::string dir) {
        std::ofstream out(dir);
        std::cout.rdbuf(out.rdbuf());        
    }

    /** Emits an LW instruction.
     * @param dest_reg the destination register
     * @param offset the word offset from source register
     * @param source_reg the source register
     * @param s the output stream
     * */
    void emitLoad(const std::string& dest_reg, int offset, const std::string& source_reg) {
        std::cout << LW << dest_reg << " " << offset * WORD_SIZE << "(" << source_reg << ")" << std::endl;
    }

    /** Emits an LW instruction without the offset.
     * @param dest_reg the destination register
     * @param source_reg the source register
     * @param s the output stream
    */
    void emitLoad(const std::string& dest_reg, const std::string& source_reg) {
        std::cout << LW << dest_reg << " " << source_reg << std::endl;
    }

    /** Emits an SW instruction.
     * @param dest_reg the destination register
     * @param offset the word offset from source register
     * @param source_reg the source register
     * @param s the output stream
     * */
    void emitStore(const std::string& dest_reg, int offset, const std::string& source_reg) {
        std::cout << SW << dest_reg << " " << offset * WORD_SIZE << "(" << source_reg << ")" << std::endl;
    }

    /** Emits an SW instruction without the offset.
     * @param dest_reg the destination register
     * @param source_reg the source register
     * @param s the output stream
     * */
    void emitStore(const std::string& dest_reg, const std::string& source_reg) {
        std::cout << SW << dest_reg << " " << source_reg << std::endl;
    }

    /** Emits the LI instruction.
     * @param dest_reg the destination register
     * @param val the value
     * @param s the output stream
     * */
    void emitLoadImm(const std::string& dest_reg, std::string val) {
        std::cout << LI << dest_reg << " " << val << std::endl;
    }

    /** Emits an LA instruction.
     * @param dest_reg the destination register
     * @param address the address from which a word is loaded
     * @param s the output stream
     * */
    void emitLoadAddress(const std::string& dest_reg, const std::string& address) {
        std::cout << LA << dest_reg << " " << address << std::endl;
    }

    /** Emits an LA instruction without the address part.
     * @param dest_reg the destination register
     * @param s the output stream
     * */
    void emitPartialLoadAddress(const std::string& dest_reg) {
        std::cout << LA << dest_reg << " ";
    }

    /** Emits a MOVE instruction.
     * @param dest_reg the destination register
     * @param source_reg the source register
     * @param s the output stream
     * */
    void emitMove(const std::string& dest_reg, const std::string& source_reg) {
        std::cout << MOVE << dest_reg << " " << source_reg << std::endl;
    }

    /** Emits a NEG instruction.
     * @param dest_reg the destination register
     * @param source_reg the source register
     * @param s the output stream
     * */
    void emitNeg(const std::string& dest_reg, const std::string& source_reg) {
        std::cout << NEG << dest_reg << " " << source_reg << std::endl;
    }

    /** Emits a NOR instruction.
     * @param dest_reg the destination register
     * @param source_reg1 the first source register
     * @param source_reg2 the second source register
     * @param s the output stream
    */

    void emitNor(const std::string& dest_reg, const std::string& source_reg1, const std::string& source_reg2) {
        std::cout << NOR << dest_reg << " " << source_reg1 << " " << source_reg2 << std::endl;
    }

    /** Emits an ADD instruction.
     * @param dest_reg the destination register
     * @param source_reg1 the first source register
     * @param source_reg2 the second source register
     * @param s the output stream
     * */
    void emitAdd(const std::string& dest_reg, const std::string& source_reg1, const std::string& source_reg2) {
        std::cout << ADD << dest_reg << " " << source_reg1 << " " << source_reg2 << std::endl;
    }

    /** Emits an ADDI instruction.
     * @param dest_reg the destination register
     * @param source_reg the source register
     * @param imm the immediate value
     * @param s the output stream
     * */    
    void emitAddImm(const std::string& dest_reg, const std::string& source_reg, int imm) {
        std::cout << ADDI << dest_reg << " " << source_reg << " " << imm << std::endl;
    }

    /** Emits an ADDU instruction.
     * @param dest_reg the destination register
     * @param source_reg1 the first source register
     * @param source_reg2 the second source register
     * @param s the output stream
     * */
    void emitAddu(const std::string& dest_reg, const std::string& source_reg1, const std::string& source_reg2) {
        std::cout << ADDU << dest_reg << " " << source_reg1 << " " << source_reg2 << std::endl;
    }

    /** Emits an ADDIU instruction.
     * @param dest_reg the destination register
     * @param source_reg the source register
     * @param imm the immediate value
     * @param s the output stream
     * */
    void emitAddiu(const std::string& dest_reg, const std::string& source_reg, int imm) {
        std::cout << ADDIU << dest_reg << " " << source_reg << " " << imm << std::endl;
    }

    /** Emits a DIV instruction.
     * @param dest_reg the destination register
     * @param source_reg1 the first source register
     * @param source_reg2 the second source register
     * @param s the output stream
     * */
    void emitDiv(const std::string& dest_reg, const std::string& source_reg1, const std::string& source_reg2) {
        std::cout << DIV << dest_reg << " " << source_reg1 << " " << source_reg2 << std::endl;
    }

    /** Emits a MUL instruction.
     * @param dest_reg the destination register
     * @param source_reg1 the first source register
     * @param source_reg2 the second source register
     * @param s the output stream
     * */
    void emitMul(const std::string& dest_reg, const std::string& source_reg1, const std::string& source_reg2) {
        std::cout << MUL << dest_reg << " " << source_reg1 << " " << source_reg2 << std::endl;
    }

    /** Emits a SUB instruction.
     * @param dest_reg the destination register
     * @param source_reg1 the first source register
     * @param source_reg2 the second source register
     * @param s the output stream
     * */
    void emitSub(const std::string& dest_reg, const std::string& source_reg1, const std::string& source_reg2) {
        std::cout << SUB << dest_reg << " " << source_reg1 << " " << source_reg2 << std::endl;
    }

    /** Emits a SLL instruction.
     * @param dest_reg the destination register
     * @param source_reg the source register
     * @param num the number of bits to shift
     * @param s the output stream
     * */
    void emitSll(const std::string& dest_reg, const std::string& source_reg, int num) {
        std::cout << SLL << dest_reg << " " << source_reg << " " << num << std::endl;
    }

    /** Emits a BEQZ instruction.
     * @param source_reg the source register
     * @param label the label to branch to
     * @param s the output stream
     * */
    void emitBeqz(const std::string& source_reg, const std::string& label) {
        std::cout << BEQZ << source_reg << " " << label << std::endl;
    }

    /** Emits a branch to the given label.
     * @param label the label to branch to
     * @param s the output stream
     * */
    void emitBranch(const std::string& label) {
        std::cout << BRANCH << label << std::endl;
    }

    /** Emits a BEQ instruction.
     * @param reg1 the first register
     * @param reg2 the second register
     * @param label the label to branch to
     * @param s the output stream
     * */
    void emitBeq(const std::string& reg1, const std::string& reg2, const std::string& label) {
        std::cout << BEQ << reg1 << " " << reg2 << " " << label << std::endl;
    }

    /** Emits a BNE instruction.
     * @param reg1 the first register
     * @param reg2 the second register
     * @param label the label to branch to
     * @param s the output stream
     * */
    void emitBne(const std::string& reg1, const std::string& reg2, const std::string& label) {
        std::cout << BNE << reg1 << " " << reg2 << " " << label << std::endl;
    }

    /** Emits a BLEQ instruction.
     * @param reg1 the first register
     * @param reg2 the second register
     * @param label the label to branch to
     * @param s the output stream
     * */
    void emitBleq(const std::string& reg1, const std::string& reg2, const std::string& label) {
        std::cout << BLEQ << reg1 << " " << reg2 << " " << label << std::endl;
    }

    /** Emits a BLT instruction.
     * @param reg1 the first register
     * @param reg2 the second register
     * @param label the label to branch to
     * @param s the output stream
     * */
    void emitBlt(const std::string& reg1, const std::string& reg2, const std::string& label) {
        std::cout << BLT << reg1 << " " << reg2 << " " << label << std::endl;
    }

    /** Emits a BGT instruction.
     * @param reg1 the first register
     * @param reg2 the second register
     * @param label the label to branch to
     * @param s the output stream
     * */
    void emitBgt(const std::string& reg1, const std::string& reg2, const std::string& label) {
        std::cout << BGT << reg1 << " " << reg2 << " " << label << std::endl;
    }

    /** Emits a JALR instruction.
     * @param dest_reg the destination register
     * @param s the output stream
     * */
    void emitJalr(const std::string& dest_reg) {
        std::cout << JALR << dest_reg << std::endl;
    }

    /** Emits a JAL instruction.
     * @param dest the destination address
     * @param s the output stream
     * */
    void emitJal(const std::string& dest) {
        std::cout << JAL << dest << std::endl;
    }

    /** Emits a RET instruction.
     * @param s the output stream
     * */
    void emitRet() {
        std::cout << RET << std::endl;
    }

    /** Emits a sequence of instructions to push a register onto the stack.
     * @param reg the register to push
     * @param s the output stream
     * */
    void emitPush(const std::string& reg) {
        emitStore(reg, 0, SP);
        emitAddiu(SP, SP, -WORD_SIZE);
    }

    /** Emits a sequence of instructions to push a register onto the stack.
     * @param reg the register to push
     * @param s the output stream
     * */
    void emitPop(const std::string& reg) {
        emitLoad(reg, 1, SP);
        emitAddiu(SP, SP, WORD_SIZE);
    }

    /** Emits a sequence of instructions to store a register in a stack location.
     * @param reg the register to store
     * @param offset the offset from the stack pointer
     * @param s the output stream
     * */
    void emitStoreStack(const std::string& reg, int offset) {
        emitStore(reg, offset, SP);
    }

    /** Emits a sequence of instructions to load a register from a stack location.
     * @param reg the register to load
     * @param offset the offset from the stack pointer
     * @param s the output stream
     * */
    void emitLoadStack(const std::string& reg, int offset) {
        emitLoad(reg, offset, SP);
    }

    std::string getLabel(int label) {
        return "L" + std::to_string(label);
    }

    /** Emits a label
     * @param label the label number
     * @param s the output stream
     * */
    void emitLabel(int label) {
        std::cout << getLabel(label) << LABEL;
    }   

    /** Emits a data segment directive
     * @param s the output stream
     * */
    void emitData() {
        std::cout << "\t.data\n";
        std::cout << ALIGN;
    }

    /** Emits a text segment directive
     * @param s the output stream
     * */
    void emitText() {
        std::cout << "\t.text\n";
    }

    /** Emits a directive to allocate space in the data segment
     * @param var the name of the variable
     * @param numBytes the number of bytes to allocate
     * @param s the output stream
     * */
    void emitSpace(const std::string& var, int numBytes) {
        std::cout << var << ":\t.space " << numBytes << std::endl;
    }

    /** Emits a directive to allocate a global variable
     * @param var the name of the variable
     * @param s the output stream
     * */
    void emitGlobal(const std::string& var) {
        std::cout << GLOBAL << var << std::endl;
    }

    /** Emits a directive to define a label
     * @param label the name of the label
     * @param s the output stream
     * */
    void emitLabel(const std::string& label) {
        std::cout << label << LABEL;
    }

    void emit(const std::string& str) {
        std::cout << str << std::endl;
    }

    /** Emits a SEQ instruction.
     * @param dest_reg the destination register
     * @param source_reg1 the first source register
     * @param source_reg2 the second source register
     * @param s the output stream
    */
    void emitSeq(const std::string& dest_reg, const std::string& source_reg1, const std::string& source_reg2) {
        std::cout << SEQ << dest_reg << " " << source_reg1 << " " << source_reg2 << std::endl;
    }

    /** Emits a SNE instruction.
     * @param dest_reg the destination register
     * @param source_reg1 the first source register
     * @param source_reg2 the second source register
     * @param s the output stream
    */
    void emitSne(const std::string& dest_reg, const std::string& source_reg1, const std::string& source_reg2) {
        std::cout << SNE << dest_reg << " " << source_reg1 << " " << source_reg2 << std::endl;
    }

    /** Emits a SGE instruction.
     * @param dest_reg the destination register
     * @param source_reg1 the first source register
     * @param source_reg2 the second source register
     * @param s the output stream
    */
    void emitSge(const std::string& dest_reg, const std::string& source_reg1, const std::string& source_reg2) {
        std::cout << SGE << dest_reg << " " << source_reg1 << " " << source_reg2 << std::endl;
    }

    /** Emits a SGT instruction.
     * @param dest_reg the destination register
     * @param source_reg1 the first source register
     * @param source_reg2 the second source register
     * @param s the output stream
    */
    void emitSgt(const std::string& dest_reg, const std::string& source_reg1, const std::string& source_reg2) {
        std::cout << SGT << dest_reg << " " << source_reg1 << " " << source_reg2 << std::endl;
    }

    /** Emits a SLE instruction.
     * @param dest_reg the destination register
     * @param source_reg1 the first source register
     * @param source_reg2 the second source register
     * @param s the output stream
    */
    void emitSle(const std::string& dest_reg, const std::string& source_reg1, const std::string& source_reg2) {
        std::cout << SLE << dest_reg << " " << source_reg1 << " " << source_reg2 << std::endl;
    }

    /** Emits a SLT instruction.
     * @param dest_reg the destination register
     * @param source_reg1 the first source register
     * @param source_reg2 the second source register
     * @param s the output stream
    */
    void emitSlt(const std::string& dest_reg, const std::string& source_reg1, const std::string& source_reg2) {
        std::cout << SLT << dest_reg << " " << source_reg1 << " " << source_reg2 << std::endl;
    }

    /** Emit a string constant definition.
     * @param str the string
     * @param s the output stream
     * @param value the string value
    */
    void emitStringConstant(const std::string& str, const std::string& value) {
        emitGlobal(str);
        emitData();
        std::cout << ALIGN;
        std::cout << str << LABEL;
        std::cout << WORD << value << std::endl;
    }

    /** Emits a number constant definition. 
     * @param str the string
     * @param value the number value
     * @param s the output stream
    */
    void emitNumberConstant(const std::string& str, const std::string& value) {
        emitData();
        std::cout << str << ":" << WORD << value << std::endl;
        emitText();
    }

    void emitStartProgram() {
        emitGlobal("main");
        emitLabel("main");
    }

    void emitEndProgram() {
        emit("li $v0 10");
        emit("syscall");
    }
}

#endif // __CGENHELPER_HPP__