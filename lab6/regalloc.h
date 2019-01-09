/* function prototype from regalloc.c */

#ifndef REGALLOC_H
#define REGALLOC_H

struct RA_result {Temp_map coloring; AS_instrList il;};

struct RA_result RA_regAlloc(F_frame f, AS_instrList il);
/*
    main()
        build() & liveness()
        MakeWorkList()
        repeat
            Simplify()
            Coalesce()
            Freeze()
            SelectSpill()
        until (all empty)
        AssignColors()
        if spilledNodes <> {} then
            RewriteProgram(spilledNodes)
            main()
*/
/*
    RewriteProgram(F_frame f, AS_instrList il, G_nodeList spills);
        1.alloc temps for each spillnode
        2.traverse instlist
        3.update program instlist

*/
/*
    Simplify()
        [same as textbook]
*/
/* 
    DecrementDegree()
        [same as textbook]
*/
/*
    Coalesce()
        
/*
    SelectSpill()
        let m in spillWorkList
        spillWorkList <- spillWorkList \ {m}
        simplifyWorkList <- simplifyWorkList U {m}
        FreezeMoves(m)
*/



#endif
