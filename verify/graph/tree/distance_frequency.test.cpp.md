---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/tree/centroid_decomposition.hpp
    title: Centroid Decomposition
  - icon: ':heavy_check_mark:'
    path: graph/tree/distance_frequency.hpp
    title: Tree Distance Frequency
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
    links:
    - https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
  bundledCode: "#line 1 \"verify/graph/tree/distance_frequency.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T\
    \ = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int to;\n\
    \    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()),\
    \ id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_\
    \ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_),\
    \ alive(alive_) {}\n\n    int other(int v) const {\n        assert(v == from ||\
    \ v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\n\
    struct Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n \
    \  private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n\
    \   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n)\
    \ : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        int idx = int(_g[from].size());\n     \
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        _g[u].push_back(edge_type(u,\
    \ v, cost, id));\n        int v_idx = int(_g[v].size());\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/tree/distance_frequency.hpp\"\n\n\n\n#include <algorithm>\n\
    #line 6 \"graph/tree/distance_frequency.hpp\"\n#include <cstddef>\n#include <cstdint>\n\
    #line 10 \"graph/tree/distance_frequency.hpp\"\n\n#line 1 \"math/fps/convolution.hpp\"\
    \n\n\n\n#line 5 \"math/fps/convolution.hpp\"\n#include <array>\n#line 8 \"math/fps/convolution.hpp\"\
    \n#include <cstring>\n#include <new>\n#include <type_traits>\n#line 13 \"math/fps/convolution.hpp\"\
    \n\n#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))\n\
    #include <immintrin.h>\n#define M1UNE_FPS_HAS_X86_SIMD 1\n#pragma GCC push_options\n\
    #pragma GCC target(\"avx2,bmi\")\n#endif\n\n#line 1 \"math/fps/internal/ntt998_faster.hpp\"\
    \n\n\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\n#line 9 \"math/fps/internal/ntt998_faster.hpp\"\
    \n\n#include <immintrin.h>\n\nnamespace m1une {\nnamespace fps {\nnamespace internal\
    \ {\nnamespace fast998_v2 {\n\n// Fixed-modulus AVX2 transform with an in-register\
    \ degree-8 residue product.\n\nusing u32=unsigned;\nusing u64=unsigned long long;\n\
    using idt=std::size_t;\nusing I256=__m256i;\ninline void store256(void*p,I256\
    \ x){\n    _mm256_store_si256((I256*)p,x);\n}\ninline I256 load256(const void*p){\n\
    \    return _mm256_load_si256((const I256*)p);\n}\nconstexpr u32 shrk(u32 x,u32\
    \ M){\n    return std::min(x,x-M);\n}\nconstexpr u32 dilt(u32 x,u32 M){\n    return\
    \ std::min(x,x+M);\n}\nconstexpr u32 reduce(u64 x,u32 niv,u32 M){\n    return\
    \ (x+u64(u32(x)*niv)*M)>>32;\n}\nconstexpr u32 mul(u32 x,u32 y,u32 niv,u32 M){\n\
    \    return reduce(u64(x)*y,niv,M);\n}\nconstexpr u32 mul_s(u32 x,u32 y,u32 niv,u32\
    \ M){\n    return shrk(reduce(u64(x)*y,niv,M),M);\n}\nconstexpr u32 qpw(u32 a,u32\
    \ b,u32 niv,u32 M,u32 r){\n    for(;b;b>>=1,a=mul(a,a,niv,M)){\n        if(b&1){\n\
    \            r=mul(r,a,niv,M);\n        }\n    }\n    return r;\n}\nconstexpr\
    \ u32 qpw_s(u32 a,u32 b,u32 niv,u32 M,u32 r){\n    return shrk(qpw(a,b,niv,M,r),M);\n\
    }\ninline I256 shrk32(I256 x,I256 M){\n    return _mm256_min_epu32(x,_mm256_sub_epi32(x,M));\n\
    }\ninline I256 dilt32(I256 x,I256 M){\n    return _mm256_min_epu32(x,_mm256_add_epi32(x,M));\n\
    }\ninline I256 Ladd32(I256 x,I256 y,I256){\n    return _mm256_add_epi32(x,y);\n\
    }\ninline I256 Lsub32(I256 x,I256 y,I256 M){\n    return _mm256_add_epi32(_mm256_sub_epi32(x,y),M);\n\
    }\ninline I256 add32(I256 x,I256 y,I256 M){\n    return shrk32(_mm256_add_epi32(x,y),M);\n\
    }\ninline I256 sub32(I256 x,I256 y,I256 M){\n    return dilt32(_mm256_sub_epi32(x,y),M);\n\
    }\ntemplate<int msk>inline I256 neg32_m(I256 x,I256 M){\n    return _mm256_blend_epi32(x,_mm256_sub_epi32(M,x),msk);\n\
    }\ninline I256 reduce(I256 a,I256 b,I256 niv,I256 M){\n    I256 c=_mm256_mul_epu32(a,niv),d=_mm256_mul_epu32(b,niv);\n\
    \    c=_mm256_mul_epu32(c,M),d=_mm256_mul_epu32(d,M);\n    return _mm256_blend_epi32(_mm256_srli_epi64(_mm256_add_epi64(a,c),32),_mm256_add_epi64(b,d),0xaa);\n\
    }\ninline I256 mul(I256 a,I256 b,I256 niv,I256 M){\n    return reduce(_mm256_mul_epu32(a,b),_mm256_mul_epu32(_mm256_srli_epi64(a,32),_mm256_srli_epi64(b,32)),niv,M);\n\
    }\ninline I256 mul_s(I256 a,I256 b,I256 niv,I256 M){\n    return shrk32(mul(a,b,niv,M),M);\n\
    }\ninline I256 mul_bsm(I256 a,I256 b,I256 niv,I256 M){\n    return reduce(_mm256_mul_epu32(a,b),_mm256_mul_epu32(_mm256_srli_epi64(a,32),b),niv,M);\n\
    }\ninline I256 mul_bsmfxd(I256 a,I256 b,I256 bniv,I256 M){\n    I256 cc=_mm256_mul_epu32(a,bniv),dd=_mm256_mul_epu32(_mm256_srli_epi64(a,32),bniv);\n\
    \    I256 c=_mm256_mul_epu32(a,b),d=_mm256_mul_epu32(_mm256_srli_epi64(a,32),b);\n\
    \    cc=_mm256_mul_epu32(cc,M),dd=_mm256_mul_epu32(dd,M);\n    return _mm256_blend_epi32(_mm256_srli_epi64(_mm256_add_epi64(c,cc),32),_mm256_add_epi64(d,dd),0xaa);\n\
    }\ninline I256 mul_bfxd(I256 a,I256 b,I256 bniv,I256 M){\n    I256 cc=_mm256_mul_epu32(a,bniv),dd=_mm256_mul_epu32(_mm256_srli_epi64(a,32),_mm256_srli_epi64(bniv,32));\n\
    \    I256 c=_mm256_mul_epu32(a,b),d=_mm256_mul_epu32(_mm256_srli_epi64(a,32),_mm256_srli_epi64(b,32));\n\
    \    cc=_mm256_mul_epu32(cc,M),dd=_mm256_mul_epu32(dd,M);\n    return _mm256_blend_epi32(_mm256_srli_epi64(_mm256_add_epi64(c,cc),32),_mm256_add_epi64(d,dd),0xaa);\n\
    }\ninline I256 mul_upd_rt(I256 a,I256 bu,I256 M){\n    I256 cc=_mm256_mul_epu32(a,bu),c=_mm256_mul_epu32(a,_mm256_srli_epi64(bu,32));\n\
    \    cc=_mm256_mul_epu32(cc,M);\n    return shrk32(_mm256_srli_epi64(_mm256_add_epi64(c,cc),32),M);\n\
    }\nconstexpr auto _mxlg=26,_lg_itth=6;\nconstexpr auto _itth=idt(1)<<_lg_itth;\n\
    static_assert(_lg_itth%2==0);\nstruct FNTT32_info{\n    u32 mod,mod2,niv,one,r2,r3,img,imgniv,RT1[_mxlg];\n\
    \    alignas(32) std::array<u32,8> rt3[_mxlg-2],rt3i[_mxlg-2],bwbr,bwb,bwbi,rt4[_mxlg-3],rt4niv[_mxlg-3],rt4i[_mxlg-3],rt4iniv[_mxlg-3],pr2,pr4,pr2niv,pr4niv,pr2i,pr2iniv,pr4i,pr4iniv;\n\
    \    constexpr FNTT32_info(const u32 m):mod(m),mod2(m*2),niv([&]{u32 n=2+m;for(int\
    \ i=0;i<4;++i){n*=2+m*n;}return n;}()),one((-m)%m),r2((-u64(m))%m),r3(mul_s(r2,r2,niv,m)),img{},imgniv{},RT1{},rt3{},rt3i{},bwbr{},bwb{},bwbi{},rt4{},rt4niv{},rt4i{},rt4iniv{},pr2{},pr4{},pr2niv{},pr4niv{},pr2i{},pr2iniv{},pr4i{},pr4iniv{}{\n\
    \        const int k=__builtin_ctz(m-1);\n\t\tu32 _g=mul(3,r2,niv,mod);\n    \
    \    for(;;++_g){\n            if(qpw_s(_g,mod>>1,niv,mod,one)!=one){\n      \
    \          break;\n            }\n        }\n\t\t_g=qpw(_g,mod>>k,niv,mod,one);\n\
    \        u32 rt1[_mxlg-1],rt1i[_mxlg-1];\n        rt1[k-2]=_g,rt1i[k-2]=qpw(_g,mod-2,niv,mod,one);\n\
    \        for(int i=k-2;i>0;--i){\n            rt1[i-1]=mul(rt1[i],rt1[i],niv,mod);\n\
    \            rt1i[i-1]=mul(rt1i[i],rt1i[i],niv,mod);\n        }\n        RT1[k-1]=qpw_s(_g,3,niv,mod,one);\n\
    \        for(int i=k-1;i>0;--i){\n\t\t\tRT1[i-1]=mul_s(RT1[i],RT1[i],niv,mod);\n\
    \        }\n        img=rt1[0],imgniv=img*niv;\n        bwbr={one,0,one,0,one};\n\
    \        bwb={rt1[1],0,rt1[0],0,mod-mul_s(rt1[0],rt1[1],niv,mod)};\n        bwbi={rt1i[1],0,rt1i[0],0,mul_s(rt1i[0],rt1i[1],niv,mod)};\n\
    \        u32 pr=one,pri=one;\n        for(int i=0;i<k-2;++i){\n            const\
    \ u32 r=mul_s(pr,rt1[i+1],niv,mod),ri=mul_s(pri,rt1i[i+1],niv,mod);\n        \
    \    const u32 r2=mul_s(r,r,niv,mod),r2i=mul_s(ri,ri,niv,mod);\n            const\
    \ u32 r3=mul_s(r,r2,niv,mod),r3i=mul_s(ri,r2i,niv,mod);\n            rt3[i]={r*niv,r,r2*niv,r2,r3*niv,r3};\n\
    \            rt3i[i]={ri*niv,ri,r2i*niv,r2i,r3i*niv,r3i};\n            pr=mul(pr,rt1i[i+1],niv,mod),pri=mul(pri,rt1[i+1],niv,mod);\n\
    \        }\n        pr=one,pri=one;\n        for(int i=0;i<k-3;++i){\n       \
    \     const u32 r=mul_s(pr,rt1[i+2],niv,mod),ri=mul_s(pri,rt1i[i+2],niv,mod);\n\
    \            rt4[i][0]=rt4i[i][0]=one;\n            for(int j=1;j<8;++j){\n  \
    \              rt4[i][j]=mul_s(rt4[i][j-1],r,niv,mod);\n                rt4i[i][j]=mul_s(rt4i[i][j-1],ri,niv,mod);\n\
    \            }\n            for(int j=0;j<8;++j){\n                rt4niv[i][j]=rt4[i][j]*niv;\n\
    \                rt4iniv[i][j]=rt4i[i][j]*niv;\n            }\n            pr=mul(pr,rt1i[i+2],niv,mod),pri=mul(pri,rt1[i+2],niv,mod);\n\
    \        }\n        pr2={one,one,one,img,one,one,one,img};\n        pr4={one,one,one,one,one,rt1[1],img,mul_s(img,rt1[1],niv,mod)};\n\
    \        const u32 nr2=mod-r2,imgr2=mul_s(img,r2,niv,mod);\n        pr2i={nr2,nr2,nr2,imgr2,nr2,nr2,nr2,imgr2};\n\
    \        pr4i={one,one,one,one,one,rt1i[1],rt1i[0],mul_s(rt1i[0],rt1i[1],niv,mod)};\n\
    \        for(int j=0;j<8;++j){\n            pr2niv[j]=pr2[j]*niv,pr4niv[j]=pr4[j]*niv;\n\
    \            pr2iniv[j]=pr2i[j]*niv,pr4iniv[j]=pr4i[j]*niv;\n        }\n    }\n\
    };\ninline void vector_dif(I256*const f,const idt n,const FNTT32_info*info){\n\
    \    alignas(32) std::array<u32,8> st_1[_mxlg>>1];\n    const I256 Mod=_mm256_set1_epi32(info->mod),Mod2=_mm256_set1_epi32(info->mod2),Niv=_mm256_set1_epi32(info->niv);\n\
    \    const I256 Img=_mm256_set1_epi32(info->img),ImgNiv=_mm256_set1_epi32(info->imgniv),id=_mm256_setr_epi32(0,2,0,4,0,2,0,4);\n\
    \    const int lgn=__builtin_ctzll(n);\n    std::fill(st_1,st_1+(lgn>>1),info->bwb);\n\
    \    const idt nn=n>>(lgn&1),m=std::min(n,_itth),mm=std::min(nn,_itth);\n    //\
    \ I256 rr=_mm256_set1_epi32(info->one);\n    if(nn!=n){\n        for(idt i=0;i<nn;++i){\n\
    \            auto const p0=f+i,p1=f+nn+i;\n            const auto f0=load256(p0),f1=load256(p1);\n\
    \            const auto g0=add32(f0,f1,Mod2),g1=Lsub32(f0,f1,Mod2);\n        \
    \    store256(p0,g0),store256(p1,g1);\n        }\n    }\n    for(idt L=nn>>2;L>0;L>>=2){\n\
    \        for(idt i=0;i<L;++i){\n            auto const p0=f+i,p1=p0+L,p2=p1+L,p3=p2+L;\n\
    \            const auto f1=load256(p1),f3=load256(p3),f2=load256(p2),f0=load256(p0);\n\
    \            const auto g3=mul_bsmfxd(Lsub32(f1,f3,Mod2),Img,ImgNiv,Mod),g1=add32(f1,f3,Mod2);\n\
    \            const auto g0=add32(f0,f2,Mod2),g2=sub32(f0,f2,Mod2);\n         \
    \   const auto h0=add32(g0,g1,Mod2),h1=Lsub32(g0,g1,Mod2);\n            const\
    \ auto h2=Ladd32(g2,g3,Mod2),h3=Lsub32(g2,g3,Mod2);\n            store256(p0,h0),store256(p1,h1),store256(p2,h2),store256(p3,h3);\n\
    \        }\n    }\n    for(idt j=0;j<n;j+=m){\n        int t=((j==0)?std::min(_lg_itth,lgn):__builtin_ctzll(j))&-2,p=(t-2)>>1;\n\
    \        for(idt L=(idt(1)<<t)>>2;L>=_itth;L>>=2,t-=2,--p){\n            auto\
    \ rt=load256(st_1+p);\n            const auto r1=_mm256_permutevar8x32_epi32(rt,id);\n\
    \            const auto r1Niv=_mm256_permutevar8x32_epi32(_mm256_mul_epu32(rt,Niv),id);\n\
    \            rt=mul_upd_rt(rt,load256(info->rt3+__builtin_ctzll(~j>>t)),Mod);\n\
    \            const auto r2=_mm256_shuffle_epi32(r1,_MM_PERM_BBBB),nr3=_mm256_shuffle_epi32(r1,_MM_PERM_DDDD);\n\
    \            const auto r2Niv=_mm256_shuffle_epi32(r1Niv,_MM_PERM_BBBB),nr3Niv=_mm256_shuffle_epi32(r1Niv,_MM_PERM_DDDD);\n\
    \            store256(st_1+p,rt);\n            for(idt i=0;i<L;++i){\n       \
    \         auto const p0=f+i+j,p1=p0+L,p2=p1+L,p3=p2+L;\n                const\
    \ auto f1=load256(p1),f3=load256(p3),f2=load256(p2),f0=load256(p0);\n        \
    \        const auto g1=mul_bsmfxd(f1,r1,r1Niv,Mod),ng3=mul_bsmfxd(f3,nr3,nr3Niv,Mod);\n\
    \                const auto g2=mul_bsmfxd(f2,r2,r2Niv,Mod),g0=shrk32(f0,Mod2);\n\
    \                const auto h3=mul_bsmfxd(Ladd32(g1,ng3,Mod2),Img,ImgNiv,Mod),h1=sub32(g1,ng3,Mod2);\n\
    \                const auto h0=add32(g0,g2,Mod2),h2=sub32(g0,g2,Mod2);\n     \
    \           const auto u0=Ladd32(h0,h1,Mod2),u1=Lsub32(h0,h1,Mod2);\n        \
    \        const auto u2=Ladd32(h2,h3,Mod2),u3=Lsub32(h2,h3,Mod2);\n           \
    \     store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n     \
    \       }\n        }\n        I256*const g=f+j;\n        for(idt l=mm,L=mm>>2;L;l=L,L>>=2,t-=2,--p){\n\
    \            auto rt=load256(st_1+p);\n            for(idt i=(j==0?l:0),k=(j+i)>>t;i<m;i+=l,++k){\n\
    \                const auto r1=_mm256_permutevar8x32_epi32(rt,id);\n         \
    \       const auto r2=_mm256_shuffle_epi32(r1,_MM_PERM_BBBB);\n              \
    \  const auto nr3=_mm256_shuffle_epi32(r1,_MM_PERM_DDDD);\n                for(idt\
    \ j=0;j<L;++j){\n                    auto const p0=g+i+j,p1=p0+L,p2=p1+L,p3=p2+L;\n\
    \                    const auto f1=load256(p1),f3=load256(p3),f2=load256(p2),f0=load256(p0);\n\
    \                    const auto g1=mul_bsm(f1,r1,Niv,Mod),ng3=mul_bsm(f3,nr3,Niv,Mod);\n\
    \                    const auto g2=mul_bsm(f2,r2,Niv,Mod),g0=shrk32(f0,Mod2);\n\
    \                    const auto h3=mul_bsmfxd(Ladd32(g1,ng3,Mod2),Img,ImgNiv,Mod),h1=sub32(g1,ng3,Mod2);\n\
    \                    const auto h0=add32(g0,g2,Mod2),h2=sub32(g0,g2,Mod2);\n \
    \                   const auto u0=Ladd32(h0,h1,Mod2),u1=Lsub32(h0,h1,Mod2);\n\
    \                    const auto u2=Ladd32(h2,h3,Mod2),u3=Lsub32(h2,h3,Mod2);\n\
    \                    store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n\
    \                }\n                rt=mul_upd_rt(rt,load256(info->rt3+__builtin_ctzll(~k)),Mod);\n\
    \            }\n            store256(st_1+p,rt);\n        }\n        // const\
    \ auto pr2=load256(&info->pr2),pr4=load256(&info->pr4);\n        // const auto\
    \ pr2Niv=load256(&info->pr2niv),pr4Niv=load256(&info->pr4niv);\n        // for(idt\
    \ i=j;i<j+m;++i){\n        //     auto fi=load256(f+i);\n        //     fi=mul(fi,rr,Niv,Mod);\n\
    \        //     rr=shrk32(mul_bfxd(rr,load256(info->rt4+__builtin_ctzll(~i)),load256(info->rt4niv+__builtin_ctzll(~i)),Mod),Mod);\n\
    \        //     fi=mul_bfxd(Ladd32(neg32_m<0xf0>(fi,Mod2),_mm256_permute2x128_si256(fi,fi,1),Mod2),pr4,pr4Niv,Mod);\n\
    \        //     fi=mul_bfxd(Ladd32(neg32_m<0xcc>(fi,Mod2),_mm256_shuffle_epi32(fi,0x4e),Mod2),pr2,pr2Niv,Mod);\n\
    \        //     fi=sub32(_mm256_shuffle_epi32(fi,0xb1),neg32_m<0x55>(fi,Mod2),Mod2);\n\
    \        //     store256(f+i,fi);\n        // }\n    }\n}\ntemplate<bool shrk=false>inline\
    \ void vector_dit(I256*const f,idt n,const FNTT32_info*const info){\n    alignas(32)\
    \ std::array<u32,8> st_1[_mxlg>>1];\n    const I256 Mod=_mm256_set1_epi32(info->mod),Mod2=_mm256_set1_epi32(info->mod2),Niv=_mm256_set1_epi32(info->niv);\n\
    \    const I256 Img=_mm256_set1_epi32(info->img),ImgNiv=_mm256_set1_epi32(info->imgniv),id=_mm256_setr_epi32(0,2,0,4,0,2,0,4);\n\
    \    const int lgn=__builtin_ctzll(n);\n    std::fill(st_1,st_1+(_lg_itth>>1),info->bwbr);\n\
    \    std::fill(st_1+(_lg_itth>>1),st_1+(_mxlg>>1),info->bwbi);\n    const idt\
    \ nn=n>>(lgn&1),mm=std::min(nn,_itth);\n    // I256 rr=_mm256_set1_epi32((info->mod-1)>>(lgn+3));\n\
    \    for(idt j=0;j<n;j+=mm){\n        // const auto pr2=load256(&info->pr2i),pr4=load256(&info->pr4i);\n\
    \        // const auto pr2Niv=load256(&info->pr2iniv),pr4Niv=load256(&info->pr4iniv);\n\
    \        // for(idt i=j;i<j+mm;++i){\n        //     auto fi=load256(f+i);\n \
    \       //     const auto rt=rr;\n        //     rr=shrk32(mul_bfxd(rr,load256(info->rt4i+__builtin_ctzll(~i)),load256(info->rt4iniv+__builtin_ctzll(~i)),Mod),Mod);\n\
    \        //     fi=mul_bfxd(Ladd32(neg32_m<0xaa>(fi,Mod2),_mm256_shuffle_epi32(fi,0xb1),Mod2),pr2,pr2Niv,Mod);\n\
    \        //     fi=mul_bfxd(Ladd32(neg32_m<0xcc>(fi,Mod2),_mm256_shuffle_epi32(fi,0x4e),Mod2),pr4,pr4Niv,Mod);\n\
    \        //     fi=mul(Ladd32(neg32_m<0xf0>(fi,Mod2),_mm256_permute2x128_si256(fi,fi,1),Mod2),rt,Niv,Mod);\n\
    \        //     store256(f+i,fi);\n        // }\n        I256*const g=f+j;\n \
    \       int t=2,p=0;\n        for(idt l=4,L=1;l<=mm;L=l,l<<=2,t+=2,++p){\n   \
    \         auto rt=load256(st_1+p);\n            for(idt i=0,k=j>>t;i<mm;i+=l,++k){\n\
    \                const auto r1=_mm256_permutevar8x32_epi32(rt,id);\n         \
    \       const auto r2=_mm256_shuffle_epi32(r1,_MM_PERM_BBBB);\n              \
    \  const auto r3=_mm256_shuffle_epi32(r1,_MM_PERM_DDDD);\n                for(idt\
    \ j=0;j<L;++j){\n                    auto const p0=g+i+j,p1=p0+L,p2=p1+L,p3=p2+L;\n\
    \                    const auto f0=load256(p0),f1=load256(p1),f2=load256(p2),f3=load256(p3);\n\
    \                    const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n \
    \                   const auto g2=add32(f2,f3,Mod2),g3=mul_bsmfxd(Lsub32(f3,f2,Mod2),Img,ImgNiv,Mod);\n\
    \                    const auto h0=Ladd32(g0,g2,Mod2),h1=Ladd32(g1,g3,Mod2);\n\
    \                    const auto h2=Lsub32(g0,g2,Mod2),h3=Lsub32(g1,g3,Mod2);\n\
    \                    const auto u0=shrk32(h0,Mod2),u1=mul_bsm(h1,r1,Niv,Mod);\n\
    \                    const auto u2=mul_bsm(h2,r2,Niv,Mod),u3=mul_bsm(h3,r3,Niv,Mod);\n\
    \                    store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n\
    \                }\n                rt=mul_upd_rt(rt,load256(info->rt3i+__builtin_ctzll(~k)),Mod);\n\
    \            }\n            store256(st_1+p,rt);\n        }\n        int tt=std::min(__builtin_ctzll(~(j>>_lg_itth))+_lg_itth,lgn);\n\
    \        for(idt L=_itth,l=L<<2;t<=tt;L=l,l<<=2,t+=2,++p){\n            if((j+_itth)==l){\n\
    \                if(shrk && l==n){\n                    for(idt i=0;i<L;++i){\n\
    \                        auto const p0=f+i,p1=p0+L,p2=p1+L,p3=p2+L;\n        \
    \                const auto f2=load256(p2),f3=load256(p3),f0=load256(p0),f1=load256(p1);\n\
    \                        const auto g3=mul_bsmfxd(Lsub32(f3,f2,Mod2),Img,ImgNiv,Mod),g2=add32(f2,f3,Mod2);\n\
    \                        const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n\
    \                        const auto h0=add32(g0,g2,Mod2),h1=add32(g1,g3,Mod2);\n\
    \                        const auto h2=sub32(g0,g2,Mod2),h3=sub32(g1,g3,Mod2);\n\
    \                        const auto u0=shrk32(h0,Mod),u1=shrk32(h1,Mod);\n   \
    \                     const auto u2=shrk32(h2,Mod),u3=shrk32(h3,Mod);\n      \
    \                  store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n\
    \                    }\n                }\n                else{\n           \
    \         for(idt i=0;i<L;++i){\n                        auto const p0=f+i,p1=p0+L,p2=p1+L,p3=p2+L;\n\
    \                        const auto f2=load256(p2),f3=load256(p3),f0=load256(p0),f1=load256(p1);\n\
    \                        const auto g3=mul_bsmfxd(Lsub32(f3,f2,Mod2),Img,ImgNiv,Mod),g2=add32(f2,f3,Mod2);\n\
    \                        const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n\
    \                        const auto h0=add32(g0,g2,Mod2),h1=add32(g1,g3,Mod2);\n\
    \                        const auto h2=sub32(g0,g2,Mod2),h3=sub32(g1,g3,Mod2);\n\
    \                        store256(p0,h0),store256(p1,h1),store256(p2,h2),store256(p3,h3);\n\
    \                    }\n                }\n            }\n            else{\n\
    \                auto rt=load256(st_1+p);\n                const auto r1=_mm256_permutevar8x32_epi32(rt,id);\n\
    \                const auto r1Niv=_mm256_permutevar8x32_epi32(_mm256_mul_epu32(rt,Niv),id);\n\
    \                rt=mul_upd_rt(rt,load256(info->rt3i+__builtin_ctzll(~j>>t)),Mod);\n\
    \                const auto r2=_mm256_shuffle_epi32(r1,_MM_PERM_BBBB),r3=_mm256_shuffle_epi32(r1,_MM_PERM_DDDD);\n\
    \                const auto r2Niv=_mm256_shuffle_epi32(r1Niv,_MM_PERM_BBBB),r3Niv=_mm256_shuffle_epi32(r1Niv,_MM_PERM_DDDD);\n\
    \                store256(st_1+p,rt);\n                for(idt i=0;i<L;++i){\n\
    \                    auto const p0=f+j+_itth-l+i,p1=p0+L,p2=p1+L,p3=p2+L;\n  \
    \                  const auto f0=load256(p0),f1=load256(p1),f2=load256(p2),f3=load256(p3);\n\
    \                    const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n \
    \                   const auto g2=add32(f2,f3,Mod2),g3=mul_bsmfxd(Lsub32(f3,f2,Mod2),Img,ImgNiv,Mod);\n\
    \                    const auto h0=Ladd32(g0,g2,Mod2),h1=Ladd32(g1,g3,Mod2);\n\
    \                    const auto h2=Lsub32(g0,g2,Mod2),h3=Lsub32(g1,g3,Mod2);\n\
    \                    const auto u0=shrk32(h0,Mod2),u1=mul_bsmfxd(h1,r1,r1Niv,Mod);\n\
    \                    const auto u2=mul_bsmfxd(h2,r2,r2Niv,Mod),u3=mul_bsmfxd(h3,r3,r3Niv,Mod);\n\
    \                    store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n\
    \                }\n            }\n        }\n    }\n    if(shrk && nn==n && n<=_itth){\n\
    \        for(idt i=0;i<n;++i){\n            const auto f0=load256(f+i);\n    \
    \        store256(f+i,shrk32(f0,Mod));\n        }\n    }\n    if(nn!=n){\n   \
    \     for(idt i=0;i<nn;++i){\n            auto const p0=f+i,p1=f+nn+i;\n     \
    \       const auto f0=load256(p0),f1=load256(p1);\n            const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n\
    \            if constexpr(shrk){\n                const auto h0=shrk32(g0,Mod),h1=shrk32(g1,Mod);\n\
    \                store256(p0,h0),store256(p1,h1);\n            }\n           \
    \ else{\n                store256(p0,g0),store256(p1,g1);\n            }\n   \
    \     }\n    }\n}\n// Returns fx * f[0,8) * g[0,8) (mod x^8 - ww).\n[[gnu::always_inline]]\
    \ inline I256 convolve8(const I256*f,const I256*g,I256 ww,I256 fx,I256 Niv,I256\
    \ Mod,I256 Mod2){\n    const auto raa=load256(f),rbb=load256(g);\n    const auto\
    \ taa=shrk32(raa,Mod2),bb=shrk32(mul_bsm(rbb,fx,Niv,Mod),Mod);\n    const auto\
    \ aw=shrk32(mul_bsm(taa,ww,Niv,Mod),Mod);\n    const auto aa=shrk32(taa,Mod);\n\
    \    const auto awa=_mm256_permute2x128_si256(aa,aw,3);\n    \n    const auto\
    \ b0=_mm256_permute4x64_epi64(bb,0x00),b1=_mm256_shuffle_epi32(b0,_MM_PERM_CDAB);\n\
    \    const auto a0=aa,a1=_mm256_srli_epi64(a0,32);\n    const auto aw7=_mm256_alignr_epi8(aa,awa,12);\n\
    \    auto res00=_mm256_mul_epu32(a0,b0);\n    auto res01=_mm256_mul_epu32(a1,b0);\n\
    \    auto res10=_mm256_mul_epu32(aw7,b1);\n    auto res11=_mm256_mul_epu32(a0,b1);\n\
    \n    const auto b2=_mm256_permute4x64_epi64(bb,0x55),b3=_mm256_shuffle_epi32(b2,_MM_PERM_CDAB);\n\
    \    const auto aw6=_mm256_alignr_epi8(aa,awa,8);\n    const auto aw5=_mm256_alignr_epi8(aa,awa,4);\n\
    \    res00=_mm256_add_epi64(res00,_mm256_mul_epu32(aw6,b2));\n    res01=_mm256_add_epi64(res01,_mm256_mul_epu32(aw7,b2));\n\
    \    res10=_mm256_add_epi64(res10,_mm256_mul_epu32(aw5,b3));\n    res11=_mm256_add_epi64(res11,_mm256_mul_epu32(aw6,b3));\n\
    \n    const auto b4=_mm256_permute4x64_epi64(bb,0xaa),b5=_mm256_shuffle_epi32(b4,_MM_PERM_CDAB);\n\
    \    const auto aw3=_mm256_alignr_epi8(awa,aw,12);\n    res00=_mm256_add_epi64(res00,_mm256_mul_epu32(awa,b4));\n\
    \    res01=_mm256_add_epi64(res01,_mm256_mul_epu32(aw5,b4));\n    res10=_mm256_add_epi64(res10,_mm256_mul_epu32(aw3,b5));\n\
    \    res11=_mm256_add_epi64(res11,_mm256_mul_epu32(awa,b5));\n\n    const auto\
    \ b6=_mm256_permute4x64_epi64(bb,0xff),b7=_mm256_shuffle_epi32(b6,_MM_PERM_CDAB);\n\
    \    const auto aw2=_mm256_alignr_epi8(awa,aw,8);\n    const auto aw1=_mm256_alignr_epi8(awa,aw,4);\n\
    \    res00=_mm256_add_epi64(res00,_mm256_mul_epu32(aw2,b6));\n    res01=_mm256_add_epi64(res01,_mm256_mul_epu32(aw3,b6));\n\
    \    res10=_mm256_add_epi64(res10,_mm256_mul_epu32(aw1,b7));\n    res11=_mm256_add_epi64(res11,_mm256_mul_epu32(aw2,b7));\n\
    \n    res00=_mm256_add_epi64(res00,res10);\n    res01=_mm256_add_epi64(res01,res11);\n\
    \n    return shrk32(reduce(res00,res01,Niv,Mod),Mod2);\n}\ninline void vector_convolution_direct(I256*f,const\
    \ I256*g,idt lm,const FNTT32_info*const info){\n    u32 RR=info->one;\n    const\
    \ auto mod=info->mod,niv=info->niv;\n    const auto Fx=_mm256_set1_epi32(mul_s((mod-((mod-1)>>(__builtin_ctzll(lm)))),info->r3,niv,mod));\n\
    \    const auto Niv=_mm256_set1_epi32(niv),Mod=_mm256_set1_epi32(mod),Mod2=_mm256_set1_epi32(info->mod2);\n\
    \    for(idt i=0;i<lm;++i){\n        store256(f+i,convolve8(f+i,g+i,_mm256_set1_epi32(RR),Fx,Niv,Mod,Mod2));\n\
    \        RR=mul(RR,info->RT1[__builtin_ctzll(~i)],niv,mod);\n    }\n}\ninline\
    \ void vector_convolution_accumulate(I256*const result,const I256*const f,\n \
    \                                         const I256*const g,idt lm,\n       \
    \                                   const FNTT32_info*const info){\n    u32 RR=info->one;\n\
    \    const auto mod=info->mod,niv=info->niv;\n    const auto Fx=_mm256_set1_epi32(mul_s((mod-((mod-1)>>(__builtin_ctzll(lm)))),info->r3,niv,mod));\n\
    \    const auto Niv=_mm256_set1_epi32(niv),Mod=_mm256_set1_epi32(mod),Mod2=_mm256_set1_epi32(info->mod2);\n\
    \    for(idt i=0;i<lm;++i){\n        const auto product=convolve8(f+i,g+i,_mm256_set1_epi32(RR),Fx,Niv,Mod,Mod2);\n\
    \        store256(result+i,add32(load256(result+i),product,Mod2));\n        RR=mul(RR,info->RT1[__builtin_ctzll(~i)],niv,mod);\n\
    \    }\n}\n\n}  // namespace fast998_v2\n}  // namespace internal\n}  // namespace\
    \ fps\n}  // namespace m1une\n\n#endif  // M1UNE_FPS_HAS_X86_SIMD\n\n\n#line 22\
    \ \"math/fps/convolution.hpp\"\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n#pragma GCC pop_options\n\
    #endif\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"math/modint.hpp\"\n#include\
    \ <iostream>\n#line 9 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus,\
    \ \"Modulus must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n\
    \    static constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n   \
    \ static constexpr ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n    \
    \    x._v = v;\n        return x;\n    }\n\n    constexpr ModInt() noexcept :\
    \ _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
    \ int> = 0>\n    constexpr ModInt(Integer v) noexcept {\n        if constexpr\
    \ (std::is_signed_v<Integer>) {\n            int64_t x = static_cast<int64_t>(v)\
    \ % static_cast<int64_t>(Modulus);\n            if (x < 0) x += Modulus;\n   \
    \         _v = static_cast<uint32_t>(x);\n        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1 % Modulus);\n        ModInt x = n < 0 ? inv() : *this;\n       \
    \ uint64_t exponent = n < 0 ? uint64_t(-(n + 1)) + 1 : uint64_t(n);\n        while\
    \ (exponent > 0) {\n            if (exponent & 1) res *= x;\n            x *=\
    \ x;\n            exponent >>= 1;\n        }\n        return res;\n    }\n\n \
    \   constexpr ModInt inv() const noexcept {\n        int64_t a = _v, b = Modulus,\
    \ u = 1, v = 0;\n        while (b) {\n            int64_t t = a / b;\n       \
    \     a -= t * b;\n            std::swap(a, b);\n            u -= t * v;\n   \
    \         std::swap(u, v);\n        }\n        assert(a == 1);\n        u %= Modulus;\n\
    \        if (u < 0) u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& os, const ModInt&\
    \ rhs) {\n        return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\ntemplate <int Id = 0>\nstruct\
    \ DynamicModInt {\n   private:\n    uint32_t _v;\n    inline static uint32_t _mod\
    \ = 1;\n\n   public:\n    static uint32_t mod() noexcept {\n        return _mod;\n\
    \    }\n\n    static void set_mod(uint32_t modulus) noexcept {\n        assert(modulus\
    \ > 0);\n        assert(modulus <= uint32_t(1) << 31);\n        _mod = modulus;\n\
    \    }\n\n    static DynamicModInt raw(uint32_t v) noexcept {\n        assert(v\
    \ < _mod);\n        DynamicModInt x;\n        x._v = v;\n        return x;\n \
    \   }\n\n    DynamicModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    DynamicModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(_mod);\n     \
    \       if (x < 0) x += _mod;\n            _v = static_cast<uint32_t>(x);\n  \
    \      } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % _mod);\n        }\n    }\n\n    uint32_t val() const noexcept {\n        return\
    \ _v;\n    }\n\n    DynamicModInt& operator++() noexcept {\n        _v++;\n  \
    \      if (_v == _mod) _v = 0;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator--() noexcept {\n        if (_v == 0) _v = _mod;\n        _v--;\n  \
    \      return *this;\n    }\n\n    DynamicModInt operator++(int) noexcept {\n\
    \        DynamicModInt result = *this;\n        ++*this;\n        return result;\n\
    \    }\n\n    DynamicModInt operator--(int) noexcept {\n        DynamicModInt\
    \ result = *this;\n        --*this;\n        return result;\n    }\n\n    DynamicModInt&\
    \ operator+=(const DynamicModInt& rhs) noexcept {\n        _v += rhs._v;\n   \
    \     if (_v >= _mod) _v -= _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator-=(const DynamicModInt& rhs) noexcept {\n        _v -= rhs._v;\n   \
    \     if (_v >= _mod) _v += _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator*=(const DynamicModInt& rhs) noexcept {\n        _v = static_cast<uint32_t>(uint64_t(_v)\
    \ * rhs._v % _mod);\n        return *this;\n    }\n\n    DynamicModInt& operator/=(const\
    \ DynamicModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n\
    \    DynamicModInt operator+(const DynamicModInt& rhs) const noexcept {\n    \
    \    return DynamicModInt(*this) += rhs;\n    }\n\n    DynamicModInt operator-(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) -=\
    \ rhs;\n    }\n\n    DynamicModInt operator*(const DynamicModInt& rhs) const noexcept\
    \ {\n        return DynamicModInt(*this) *= rhs;\n    }\n\n    DynamicModInt operator/(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) /=\
    \ rhs;\n    }\n\n    bool operator==(const DynamicModInt& rhs) const noexcept\
    \ {\n        return _v == rhs._v;\n    }\n\n    bool operator!=(const DynamicModInt&\
    \ rhs) const noexcept {\n        return _v != rhs._v;\n    }\n\n    DynamicModInt\
    \ pow(long long exponent) const noexcept {\n        DynamicModInt result = raw(1\
    \ % _mod);\n        DynamicModInt base = exponent < 0 ? inv() : *this;\n     \
    \   uint64_t magnitude =\n            exponent < 0 ? uint64_t(-(exponent + 1))\
    \ + 1 : uint64_t(exponent);\n        while (magnitude > 0) {\n            if (magnitude\
    \ & 1) result *= base;\n            base *= base;\n            magnitude >>= 1;\n\
    \        }\n        return result;\n    }\n\n    DynamicModInt inv() const noexcept\
    \ {\n        int64_t a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n  \
    \          int64_t quotient = a / b;\n            a -= quotient * b;\n       \
    \     std::swap(a, b);\n            u -= quotient * v;\n            std::swap(u,\
    \ v);\n        }\n        assert(a == 1);\n        u %= _mod;\n        if (u <\
    \ 0) u += _mod;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const DynamicModInt& rhs) {\n   \
    \     return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, DynamicModInt& rhs) {\n        long long value;\n        is >> value;\n\
    \        rhs = DynamicModInt(value);\n        return is;\n    }\n};\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 27 \"math/fps/convolution.hpp\"\n\nnamespace\
    \ m1une {\nnamespace fps {\n\nnamespace internal {\n\ntemplate <class Mint, class\
    \ = void>\nstruct has_static_modulus : std::false_type {};\n\ntemplate <class\
    \ Mint>\nstruct has_static_modulus<\n    Mint, std::void_t<decltype(std::integral_constant<uint32_t,\
    \ Mint::mod()>{})>>\n    : std::true_type {};\n\nconstexpr uint32_t primitive_root_constexpr(uint32_t\
    \ mod) {\n    if (mod == 2) return 1;\n    if (mod == 167772161) return 3;\n \
    \   if (mod == 469762049) return 3;\n    if (mod == 754974721) return 11;\n  \
    \  if (mod == 998244353) return 3;\n    if (mod == 1224736769) return 3;\n\n \
    \   uint32_t divisors[32] = {};\n    int count = 0;\n    uint32_t x = mod - 1;\n\
    \    for (uint32_t p = 2; uint64_t(p) * p <= x; p++) {\n        if (x % p != 0)\
    \ continue;\n        divisors[count++] = p;\n        while (x % p == 0) x /= p;\n\
    \    }\n    if (x > 1) divisors[count++] = x;\n\n    for (uint32_t g = 2;; g++)\
    \ {\n        bool ok = true;\n        for (int i = 0; i < count; i++) {\n    \
    \        uint64_t value = 1;\n            uint64_t base = g;\n            uint32_t\
    \ exponent = (mod - 1) / divisors[i];\n            while (exponent > 0) {\n  \
    \              if (exponent & 1) value = value * base % mod;\n               \
    \ base = base * base % mod;\n                exponent >>= 1;\n            }\n\
    \            if (value == 1) {\n                ok = false;\n                break;\n\
    \            }\n        }\n        if (ok) return g;\n    }\n}\n\nconstexpr int\
    \ two_adic_order(uint32_t x) {\n    int result = 0;\n    while ((x & 1) == 0)\
    \ {\n        x >>= 1;\n        result++;\n    }\n    return result;\n}\n\ntemplate\
    \ <class Mint>\nstruct NttRoots {\n    static constexpr int max_base = two_adic_order(Mint::mod()\
    \ - 1);\n    std::array<Mint, max_base + 1> root;\n    std::array<Mint, max_base\
    \ + 1> inverse_root;\n    std::array<Mint, max_base> rate;\n    std::array<Mint,\
    \ max_base> inverse_rate;\n    std::array<Mint, max_base> rate_radix4;\n    std::array<Mint,\
    \ max_base> inverse_rate_radix4;\n\n    NttRoots() {\n        constexpr uint32_t\
    \ primitive_root = primitive_root_constexpr(Mint::mod());\n        for (int level\
    \ = 1; level <= max_base; level++) {\n            root[level] = Mint(primitive_root).pow((Mint::mod()\
    \ - 1) >> level);\n            inverse_root[level] = root[level].inv();\n    \
    \    }\n        Mint product = 1;\n        Mint inverse_product = 1;\n       \
    \ for (int i = 0; i + 1 < max_base; i++) {\n            rate[i] = root[i + 2]\
    \ * product;\n            inverse_rate[i] = inverse_root[i + 2] * inverse_product;\n\
    \            product *= inverse_root[i + 2];\n            inverse_product *= root[i\
    \ + 2];\n        }\n        product = 1;\n        inverse_product = 1;\n     \
    \   for (int i = 0; i + 2 < max_base; i++) {\n            rate_radix4[i] = root[i\
    \ + 3] * product;\n            inverse_rate_radix4[i] = inverse_root[i + 3] *\
    \ inverse_product;\n            product *= inverse_root[i + 3];\n            inverse_product\
    \ *= root[i + 3];\n        }\n    }\n};\n\ntemplate <class Mint>\nconst NttRoots<Mint>&\
    \ ntt_roots() {\n    static const NttRoots<Mint> roots;\n    return roots;\n}\n\
    \ntemplate <class Mint>\nvoid ntt(std::vector<Mint>& a, bool inverse, bool normalize\
    \ = true) {\n    const int n = int(a.size());\n    assert(n > 0 && (n & (n - 1))\
    \ == 0);\n    assert((Mint::mod() - 1) % uint32_t(n) == 0);\n\n    const auto&\
    \ roots = ntt_roots<Mint>();\n    const int height = two_adic_order(uint32_t(n));\n\
    \    if (!inverse) {\n        int phase = 0;\n        while (phase < height) {\n\
    \            if (height - phase == 1) {\n                const int width = 1 <<\
    \ (height - phase - 1);\n                Mint twiddle = 1;\n                for\
    \ (int block = 0; block < (1 << phase); block++) {\n                    const\
    \ int offset = block << (height - phase);\n                    for (int i = 0;\
    \ i < width; i++) {\n                        const Mint left = a[offset + i];\n\
    \                        const Mint right = a[offset + i + width] * twiddle;\n\
    \                        a[offset + i] = left + right;\n                     \
    \   a[offset + i + width] = left - right;\n                    }\n           \
    \         if (block + 1 != (1 << phase))\n                        twiddle *= roots.rate[__builtin_ctz(~uint32_t(block))];\n\
    \                }\n                phase++;\n                continue;\n    \
    \        }\n\n            const int width = 1 << (height - phase - 2);\n     \
    \       Mint twiddle = 1;\n            const Mint imaginary = roots.root[2];\n\
    \            for (int block = 0; block < (1 << phase); block++) {\n          \
    \      const Mint twiddle2 = twiddle * twiddle;\n                const Mint twiddle3\
    \ = twiddle2 * twiddle;\n                const int offset = block << (height -\
    \ phase);\n                for (int i = 0; i < width; i++) {\n               \
    \     const uint64_t mod2 = uint64_t(Mint::mod()) * Mint::mod();\n           \
    \         const uint64_t a0 = a[offset + i].val();\n                    const\
    \ uint64_t a1 = uint64_t(a[offset + i + width].val()) * twiddle.val();\n     \
    \               const uint64_t a2 =\n                        uint64_t(a[offset\
    \ + i + 2 * width].val()) * twiddle2.val();\n                    const uint64_t\
    \ a3 =\n                        uint64_t(a[offset + i + 3 * width].val()) * twiddle3.val();\n\
    \                    const uint64_t a1na3i =\n                        uint64_t(Mint(a1\
    \ + mod2 - a3).val()) * imaginary.val();\n                    const uint64_t negative_a2\
    \ = mod2 - a2;\n                    a[offset + i] = Mint(a0 + a2 + a1 + a3);\n\
    \                    a[offset + i + width] = Mint(a0 + a2 + 2 * mod2 - a1 - a3);\n\
    \                    a[offset + i + 2 * width] = Mint(a0 + negative_a2 + a1na3i);\n\
    \                    a[offset + i + 3 * width] = Mint(a0 + negative_a2 + mod2\
    \ - a1na3i);\n                }\n                if (block + 1 != (1 << phase))\n\
    \                    twiddle *= roots.rate_radix4[__builtin_ctz(~uint32_t(block))];\n\
    \            }\n            phase += 2;\n        }\n    } else {\n        int\
    \ phase = height;\n        while (phase > 0) {\n            if (phase == 1) {\n\
    \                const int width = 1 << (height - phase);\n                Mint\
    \ twiddle = 1;\n                for (int block = 0; block < (1 << (phase - 1));\
    \ block++) {\n                    const int offset = block << (height - phase\
    \ + 1);\n                    for (int i = 0; i < width; i++) {\n             \
    \           const Mint left = a[offset + i];\n                        const Mint\
    \ right = a[offset + i + width];\n                        a[offset + i] = left\
    \ + right;\n                        a[offset + i + width] = (left - right) * twiddle;\n\
    \                    }\n                    if (block + 1 != (1 << (phase - 1)))\n\
    \                        twiddle *= roots.inverse_rate[__builtin_ctz(~uint32_t(block))];\n\
    \                }\n                phase--;\n                continue;\n    \
    \        }\n\n            const int width = 1 << (height - phase);\n         \
    \   Mint twiddle = 1;\n            const Mint inverse_imaginary = roots.inverse_root[2];\n\
    \            for (int block = 0; block < (1 << (phase - 2)); block++) {\n    \
    \            const Mint twiddle2 = twiddle * twiddle;\n                const Mint\
    \ twiddle3 = twiddle2 * twiddle;\n                const int offset = block <<\
    \ (height - phase + 2);\n                for (int i = 0; i < width; i++) {\n \
    \                   const uint64_t a0 = a[offset + i].val();\n               \
    \     const uint64_t a1 = a[offset + i + width].val();\n                    const\
    \ uint64_t a2 = a[offset + i + 2 * width].val();\n                    const uint64_t\
    \ a3 = a[offset + i + 3 * width].val();\n                    const uint64_t a2na3i\
    \ =\n                        uint64_t(Mint((Mint::mod() + a2 - a3) * inverse_imaginary.val()).val());\n\
    \                    a[offset + i] = Mint(a0 + a1 + a2 + a3);\n              \
    \      a[offset + i + width] =\n                        Mint((a0 + Mint::mod()\
    \ - a1 + a2na3i) * twiddle.val());\n                    a[offset + i + 2 * width]\
    \ = Mint(\n                        (a0 + a1 + 2ULL * Mint::mod() - a2 - a3) *\
    \ twiddle2.val());\n                    a[offset + i + 3 * width] = Mint(\n  \
    \                      (a0 + Mint::mod() - a1 + Mint::mod() - a2na3i) * twiddle3.val());\n\
    \                }\n                if (block + 1 != (1 << (phase - 2)))\n   \
    \                 twiddle *= roots.inverse_rate_radix4[__builtin_ctz(~uint32_t(block))];\n\
    \            }\n            phase -= 2;\n        }\n        if (normalize) {\n\
    \            const Mint inverse_n = Mint(n).inv();\n            for (Mint& value\
    \ : a) value *= inverse_n;\n        }\n    }\n}\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    \n#pragma GCC push_options\n#pragma GCC target(\"avx2,bmi\")\n\ntemplate <class\
    \ Mint>\n__attribute__((target(\"avx2,bmi\"), hot))\nstd::vector<Mint> convolution_998244353_simd(const\
    \ std::vector<Mint>& a,\n                                             const std::vector<Mint>&\
    \ b) {\n    const int result_size = int(a.size() + b.size() - 1);\n    int n =\
    \ 1;\n    while (n < result_size) n <<= 1;\n    auto* transformed_a = static_cast<uint32_t*>(\n\
    \        ::operator new[](sizeof(uint32_t) * n, std::align_val_t(32)));\n    auto*\
    \ transformed_b = static_cast<uint32_t*>(\n        ::operator new[](sizeof(uint32_t)\
    \ * n, std::align_val_t(32)));\n    if constexpr (std::is_same_v<Mint, math::ModInt<998244353>>)\
    \ {\n        static_assert(sizeof(Mint) == sizeof(uint32_t) && std::is_trivially_copyable_v<Mint>);\n\
    \        std::memcpy(transformed_a, a.data(), sizeof(uint32_t) * a.size());\n\
    \        std::memcpy(transformed_b, b.data(), sizeof(uint32_t) * b.size());\n\
    \    } else {\n        for (int i = 0; i < int(a.size()); i++) transformed_a[i]\
    \ = a[i].val();\n        for (int i = 0; i < int(b.size()); i++) transformed_b[i]\
    \ = b[i].val();\n    }\n    std::memset(transformed_a + a.size(), 0, sizeof(uint32_t)\
    \ * (n - a.size()));\n    std::memset(transformed_b + b.size(), 0, sizeof(uint32_t)\
    \ * (n - b.size()));\n\n    static constexpr fast998_v2::FNTT32_info transform(998244353);\n\
    \    const std::size_t vector_size = std::size_t(n) >> 3;\n    fast998_v2::vector_dif(reinterpret_cast<__m256i*>(transformed_a),\
    \ vector_size, &transform);\n    fast998_v2::vector_dif(reinterpret_cast<__m256i*>(transformed_b),\
    \ vector_size, &transform);\n    fast998_v2::vector_convolution_direct(\n    \
    \    reinterpret_cast<__m256i*>(transformed_a),\n        reinterpret_cast<const\
    \ __m256i*>(transformed_b), vector_size, &transform);\n    fast998_v2::vector_dit<true>(reinterpret_cast<__m256i*>(transformed_a),\
    \ vector_size,\n                                 &transform);\n\n    std::vector<Mint>\
    \ result(result_size);\n    for (int j = 0; j < result_size; j++) result[j] =\
    \ Mint::raw(transformed_a[j]);\n    ::operator delete[](transformed_a, std::align_val_t(32));\n\
    \    ::operator delete[](transformed_b, std::align_val_t(32));\n    return result;\n\
    }\n\n#pragma GCC pop_options\n\n#endif\n\n}  // namespace internal\n\ntemplate\
    \ <class Mint>\nstd::vector<Mint> convolution_naive(const std::vector<Mint>& a,\
    \ const std::vector<Mint>& b) {\n    if (a.empty() || b.empty()) return {};\n\
    \    std::vector<Mint> result(a.size() + b.size() - 1);\n    if (a.size() < b.size())\
    \ {\n        for (int i = 0; i < int(a.size()); i++) {\n            for (int j\
    \ = 0; j < int(b.size()); j++) result[i + j] += a[i] * b[j];\n        }\n    }\
    \ else {\n        for (int j = 0; j < int(b.size()); j++) {\n            for (int\
    \ i = 0; i < int(a.size()); i++) result[i + j] += a[i] * b[j];\n        }\n  \
    \  }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> convolution_ntt(const\
    \ std::vector<Mint>& a, const std::vector<Mint>& b) {\n    const int result_size\
    \ = int(a.size() + b.size() - 1);\n    int n = 1;\n    while (n < result_size)\
    \ n <<= 1;\n    assert((Mint::mod() - 1) % uint32_t(n) == 0);\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    \    if constexpr (Mint::mod() == 998244353) {\n        if (n >= 64 && __builtin_cpu_supports(\"\
    avx2\"))\n            return internal::convolution_998244353_simd(a, b);\n   \
    \ }\n#endif\n\n    // Allocate the padded buffers directly.  Constructing from\
    \ the inputs and\n    // then resizing used to allocate and copy both large operands\
    \ twice.\n    std::vector<Mint> fa(n);\n    std::vector<Mint> fb(n);\n    std::copy(a.begin(),\
    \ a.end(), fa.begin());\n    std::copy(b.begin(), b.end(), fb.begin());\n    internal::ntt(fa,\
    \ false);\n    internal::ntt(fb, false);\n    const Mint inverse_n = Mint(n).inv();\n\
    \    for (int i = 0; i < n; i++) fa[i] *= fb[i] * inverse_n;\n    internal::ntt(fa,\
    \ true, false);\n    fa.resize(result_size);\n    return fa;\n}\n\nnamespace internal\
    \ {\n\ntemplate <class Mint>\nstd::vector<Mint> convolution_998244353_blocked_scalar(const\
    \ std::vector<Mint>& a,\n                                                    \
    \   const std::vector<Mint>& b,\n                                            \
    \           int transform_size) {\n    assert(Mint::mod() == 998244353);\n   \
    \ assert(transform_size >= 2 && (transform_size & (transform_size - 1)) == 0);\n\
    \    assert((Mint::mod() - 1) % uint32_t(transform_size) == 0);\n\n    const int\
    \ block_size = transform_size / 2;\n    const int a_blocks = int((a.size() + block_size\
    \ - 1) / block_size);\n    const int b_blocks = int((b.size() + block_size - 1)\
    \ / block_size);\n\n    auto transform_blocks = [&](const std::vector<Mint>& values,\
    \ int block_count) {\n        std::vector<std::vector<Mint>> blocks;\n       \
    \ blocks.reserve(block_count);\n        for (int block = 0; block < block_count;\
    \ block++) {\n            const int begin = block * block_size;\n            const\
    \ int count = std::min(block_size, int(values.size()) - begin);\n            std::vector<Mint>\
    \ transformed(transform_size);\n            std::copy_n(values.begin() + begin,\
    \ count, transformed.begin());\n            ntt(transformed, false);\n       \
    \     blocks.emplace_back(std::move(transformed));\n        }\n        return\
    \ blocks;\n    };\n\n    std::vector<std::vector<Mint>> transformed_a = transform_blocks(a,\
    \ a_blocks);\n    std::vector<std::vector<Mint>> transformed_b = transform_blocks(b,\
    \ b_blocks);\n    const int result_size = int(a.size() + b.size() - 1);\n    std::vector<Mint>\
    \ result(result_size);\n    std::vector<Mint> transformed_result(transform_size);\n\
    \    for (int diagonal = 0; diagonal < a_blocks + b_blocks - 1; diagonal++) {\n\
    \        std::fill(transformed_result.begin(), transformed_result.end(), Mint(0));\n\
    \        const int first_a = std::max(0, diagonal - (b_blocks - 1));\n       \
    \ const int last_a = std::min(a_blocks - 1, diagonal);\n        for (int a_block\
    \ = first_a; a_block <= last_a; a_block++) {\n            const int b_block =\
    \ diagonal - a_block;\n            for (int i = 0; i < transform_size; i++)\n\
    \                transformed_result[i] +=\n                    transformed_a[a_block][i]\
    \ * transformed_b[b_block][i];\n        }\n        ntt(transformed_result, true);\n\
    \n        const int output_offset = diagonal * block_size;\n        const int\
    \ output_count = std::min(transform_size, result_size - output_offset);\n    \
    \    for (int i = 0; i < output_count; i++)\n            result[output_offset\
    \ + i] += transformed_result[i];\n    }\n    return result;\n}\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    \nclass AlignedUint32Buffer {\n   private:\n    uint32_t* data_;\n\n   public:\n\
    \    explicit AlignedUint32Buffer(std::size_t size)\n        : data_(static_cast<uint32_t*>(\n\
    \              ::operator new[](sizeof(uint32_t) * size, std::align_val_t(32))))\
    \ {}\n\n    AlignedUint32Buffer(const AlignedUint32Buffer&) = delete;\n    AlignedUint32Buffer&\
    \ operator=(const AlignedUint32Buffer&) = delete;\n\n    AlignedUint32Buffer(AlignedUint32Buffer&&\
    \ other) noexcept : data_(other.data_) {\n        other.data_ = nullptr;\n   \
    \ }\n\n    AlignedUint32Buffer& operator=(AlignedUint32Buffer&& other) noexcept\
    \ {\n        if (this == &other) return *this;\n        ::operator delete[](data_,\
    \ std::align_val_t(32));\n        data_ = other.data_;\n        other.data_ =\
    \ nullptr;\n        return *this;\n    }\n\n    ~AlignedUint32Buffer() {\n   \
    \     ::operator delete[](data_, std::align_val_t(32));\n    }\n\n    uint32_t*\
    \ data() {\n        return data_;\n    }\n\n    const uint32_t* data() const {\n\
    \        return data_;\n    }\n};\n\ntemplate <class Mint>\n__attribute__((target(\"\
    avx2,bmi\"), hot))\nstd::vector<Mint> convolution_998244353_blocked_simd(const\
    \ std::vector<Mint>& a,\n                                                    \
    \ const std::vector<Mint>& b,\n                                              \
    \       int transform_size) {\n    assert(Mint::mod() == 998244353);\n    assert(transform_size\
    \ >= 64 && (transform_size & (transform_size - 1)) == 0);\n    assert((Mint::mod()\
    \ - 1) % uint32_t(transform_size) == 0);\n\n    const int block_size = transform_size\
    \ / 2;\n    const int a_blocks = int((a.size() + block_size - 1) / block_size);\n\
    \    const int b_blocks = int((b.size() + block_size - 1) / block_size);\n   \
    \ static constexpr fast998_v2::FNTT32_info transform(998244353);\n    const std::size_t\
    \ vector_size = std::size_t(transform_size) / 8;\n\n    auto transform_blocks\
    \ = [&](const std::vector<Mint>& values, int block_count) {\n        std::vector<AlignedUint32Buffer>\
    \ blocks;\n        blocks.reserve(block_count);\n        for (int block = 0; block\
    \ < block_count; block++) {\n            const int begin = block * block_size;\n\
    \            const int count = std::min(block_size, int(values.size()) - begin);\n\
    \            AlignedUint32Buffer transformed(transform_size);\n            if\
    \ constexpr (std::is_same_v<Mint, math::ModInt<998244353>>) {\n              \
    \  static_assert(sizeof(Mint) == sizeof(uint32_t) &&\n                       \
    \       std::is_trivially_copyable_v<Mint>);\n                std::memcpy(transformed.data(),\
    \ values.data() + begin,\n                            sizeof(uint32_t) * count);\n\
    \            } else {\n                for (int i = 0; i < count; i++)\n     \
    \               transformed.data()[i] = values[begin + i].val();\n           \
    \ }\n            std::memset(transformed.data() + count, 0,\n                \
    \        sizeof(uint32_t) * (transform_size - count));\n            fast998_v2::vector_dif(reinterpret_cast<__m256i*>(transformed.data()),\n\
    \                                   vector_size, &transform);\n            blocks.emplace_back(std::move(transformed));\n\
    \        }\n        return blocks;\n    };\n\n    std::vector<AlignedUint32Buffer>\
    \ transformed_a = transform_blocks(a, a_blocks);\n    std::vector<AlignedUint32Buffer>\
    \ transformed_b = transform_blocks(b, b_blocks);\n    const int result_size =\
    \ int(a.size() + b.size() - 1);\n    std::vector<Mint> result(result_size);\n\
    \    AlignedUint32Buffer transformed_result(transform_size);\n    for (int diagonal\
    \ = 0; diagonal < a_blocks + b_blocks - 1; diagonal++) {\n        std::memset(transformed_result.data(),\
    \ 0, sizeof(uint32_t) * transform_size);\n        const int first_a = std::max(0,\
    \ diagonal - (b_blocks - 1));\n        const int last_a = std::min(a_blocks -\
    \ 1, diagonal);\n        for (int a_block = first_a; a_block <= last_a; a_block++)\
    \ {\n            const int b_block = diagonal - a_block;\n            fast998_v2::vector_convolution_accumulate(\n\
    \                reinterpret_cast<__m256i*>(transformed_result.data()),\n    \
    \            reinterpret_cast<const __m256i*>(transformed_a[a_block].data()),\n\
    \                reinterpret_cast<const __m256i*>(transformed_b[b_block].data()),\n\
    \                vector_size, &transform);\n        }\n        fast998_v2::vector_dit<true>(\n\
    \            reinterpret_cast<__m256i*>(transformed_result.data()), vector_size,\n\
    \            &transform);\n\n        const int output_offset = diagonal * block_size;\n\
    \        const int output_count = std::min(transform_size, result_size - output_offset);\n\
    \        for (int i = 0; i < output_count; i++) {\n            uint32_t value\
    \ = result[output_offset + i].val() + transformed_result.data()[i];\n        \
    \    if (value >= Mint::mod()) value -= Mint::mod();\n            result[output_offset\
    \ + i] = Mint::raw(value);\n        }\n    }\n    return result;\n}\n\n#endif\n\
    \ntemplate <class Mint>\nstd::vector<Mint> convolution_998244353_blocked(const\
    \ std::vector<Mint>& a,\n                                                const\
    \ std::vector<Mint>& b,\n                                                int transform_size\
    \ = 1 << 23) {\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n    if (transform_size >= 64 &&\
    \ __builtin_cpu_supports(\"avx2\"))\n        return convolution_998244353_blocked_simd(a,\
    \ b, transform_size);\n#endif\n    return convolution_998244353_blocked_scalar(a,\
    \ b, transform_size);\n}\n\n}  // namespace internal\n\ntemplate <class Mint>\n\
    std::vector<Mint> convolution(const std::vector<Mint>& a, const std::vector<Mint>&\
    \ b) {\n    if (a.empty() || b.empty()) return {};\n    if (std::min(a.size(),\
    \ b.size()) <= 32) return convolution_naive(a, b);\n\n    const int result_size\
    \ = int(a.size() + b.size() - 1);\n    int n = 1;\n    while (n < result_size)\
    \ n <<= 1;\n    if constexpr (internal::has_static_modulus<Mint>::value) {\n \
    \       if constexpr (Mint::mod() == 998244353) {\n            if (n > (1 << 23))\n\
    \                return internal::convolution_998244353_blocked(a, b);\n     \
    \   }\n        if ((Mint::mod() - 1) % uint32_t(n) == 0) return convolution_ntt(a,\
    \ b);\n    }\n\n    using Mint1 = math::ModInt<167772161>;\n    using Mint2 =\
    \ math::ModInt<469762049>;\n    using Mint3 = math::ModInt<754974721>;\n    assert(n\
    \ <= (1 << 24));\n\n    [[maybe_unused]] const unsigned __int128 coefficient_bound\
    \ =\n        static_cast<unsigned __int128>(std::min(a.size(), b.size())) * (Mint::mod()\
    \ - 1) *\n        (Mint::mod() - 1);\n    [[maybe_unused]] const unsigned __int128\
    \ crt_modulus =\n        static_cast<unsigned __int128>(Mint1::mod()) * Mint2::mod()\
    \ * Mint3::mod();\n    assert(coefficient_bound < crt_modulus);\n\n    auto converted_convolution\
    \ = [&]<class OtherMint>() {\n        std::vector<OtherMint> converted_a(a.size());\n\
    \        std::vector<OtherMint> converted_b(b.size());\n        for (int i = 0;\
    \ i < int(a.size()); i++) converted_a[i] = OtherMint(a[i].val());\n        for\
    \ (int i = 0; i < int(b.size()); i++) converted_b[i] = OtherMint(b[i].val());\n\
    \        return convolution_ntt(converted_a, converted_b);\n    };\n    std::vector<Mint1>\
    \ c1 = converted_convolution.template operator()<Mint1>();\n    std::vector<Mint2>\
    \ c2 = converted_convolution.template operator()<Mint2>();\n    std::vector<Mint3>\
    \ c3 = converted_convolution.template operator()<Mint3>();\n    static const uint64_t\
    \ inverse_mod1_mod2 = Mint2(Mint1::mod()).inv().val();\n    static const uint64_t\
    \ mod1_mod3 = Mint1::mod() % Mint3::mod();\n    static const uint64_t mod1_mod2_mod3\
    \ =\n        mod1_mod3 * (Mint2::mod() % Mint3::mod()) % Mint3::mod();\n    static\
    \ const uint64_t inverse_mod1_mod2_mod3 = Mint3(uint32_t(mod1_mod2_mod3)).inv().val();\n\
    \n    const uint64_t target_mod = Mint::mod();\n    const uint64_t mod1_target\
    \ = Mint1::mod() % target_mod;\n    const uint64_t mod1_mod2_target = mod1_target\
    \ * (Mint2::mod() % target_mod) % target_mod;\n    std::vector<Mint> result(result_size);\n\
    \    for (int i = 0; i < result_size; i++) {\n        const uint64_t r1 = c1[i].val();\n\
    \        const uint64_t r2 = c2[i].val();\n        const uint64_t r3 = c3[i].val();\n\
    \        const uint64_t first =\n            (r2 + Mint2::mod() - r1 % Mint2::mod())\
    \ % Mint2::mod() * inverse_mod1_mod2 %\n            Mint2::mod();\n        const\
    \ uint64_t combined_mod3 =\n            (r1 % Mint3::mod() + mod1_mod3 * (first\
    \ % Mint3::mod())) % Mint3::mod();\n        const uint64_t second =\n        \
    \    (r3 + Mint3::mod() - combined_mod3) % Mint3::mod() * inverse_mod1_mod2_mod3\
    \ %\n            Mint3::mod();\n\n        uint64_t value = r1 % target_mod;\n\
    \        value = (value + mod1_target * (first % target_mod)) % target_mod;\n\
    \        value = (value + mod1_mod2_target * (second % target_mod)) % target_mod;\n\
    \        result[i] = Mint::raw(uint32_t(value));\n    }\n    return result;\n\
    }\n\n}  // namespace fps\n}  // namespace m1une\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    #undef M1UNE_FPS_HAS_X86_SIMD\n#endif\n\n\n#line 1 \"graph/tree/centroid_decomposition.hpp\"\
    \n\n\n\n#line 6 \"graph/tree/centroid_decomposition.hpp\"\n\n#line 8 \"graph/tree/centroid_decomposition.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct CentroidDecomposition\
    \ {\n    int n;\n    std::vector<int> parent;\n    std::vector<int> depth;\n \
    \   std::vector<int> order;\n    std::vector<int> roots;\n    std::vector<std::vector<int>>\
    \ children;\n\n   private:\n    std::vector<int> _subtree_size;\n    std::vector<int>\
    \ _work_parent;\n    std::vector<char> _removed;\n\n    void build_component(const\
    \ m1une::graph::Graph<T>& g, int start, int p, int d) {\n        std::vector<int>\
    \ nodes;\n        std::vector<int> stack = {start};\n        _work_parent[start]\
    \ = -2;\n        while (!stack.empty()) {\n            int v = stack.back();\n\
    \            stack.pop_back();\n            nodes.push_back(v);\n            for\
    \ (const auto& e : g[v]) {\n                if (!e.alive || _removed[e.to]) continue;\n\
    \                if (_work_parent[e.to] != -1) continue;\n                _work_parent[e.to]\
    \ = v;\n                stack.push_back(e.to);\n            }\n        }\n\n \
    \       for (int v : nodes) _subtree_size[v] = 1;\n        for (int i = int(nodes.size())\
    \ - 1; i >= 0; i--) {\n            int v = nodes[i];\n            if (_work_parent[v]\
    \ >= 0) _subtree_size[_work_parent[v]] += _subtree_size[v];\n        }\n\n   \
    \     int total = int(nodes.size());\n        int centroid = start;\n        int\
    \ best = total + 1;\n        for (int v : nodes) {\n            int largest =\
    \ total - _subtree_size[v];\n            for (const auto& e : g[v]) {\n      \
    \          if (!e.alive || _removed[e.to]) continue;\n                if (_work_parent[e.to]\
    \ == v) largest = std::max(largest, _subtree_size[e.to]);\n            }\n   \
    \         if (largest < best) {\n                best = largest;\n           \
    \     centroid = v;\n            }\n        }\n\n        for (int v : nodes) _work_parent[v]\
    \ = -1;\n\n        parent[centroid] = p;\n        depth[centroid] = d;\n     \
    \   order.push_back(centroid);\n        if (p == -1) {\n            roots.push_back(centroid);\n\
    \        } else {\n            children[p].push_back(centroid);\n        }\n \
    \       _removed[centroid] = true;\n\n        for (const auto& e : g[centroid])\
    \ {\n            if (!e.alive || _removed[e.to]) continue;\n            build_component(g,\
    \ e.to, centroid, d + 1);\n        }\n    }\n\n   public:\n    CentroidDecomposition()\
    \ : n(0) {}\n    explicit CentroidDecomposition(const m1une::graph::Graph<T>&\
    \ g) {\n        build(g);\n    }\n\n    void build(const m1une::graph::Graph<T>&\
    \ g) {\n        n = g.size();\n        parent.assign(n, -1);\n        depth.assign(n,\
    \ -1);\n        order.clear();\n        order.reserve(n);\n        roots.clear();\n\
    \        children.assign(n, {});\n        _subtree_size.assign(n, 0);\n      \
    \  _work_parent.assign(n, -1);\n        _removed.assign(n, false);\n\n       \
    \ for (int v = 0; v < n; v++) {\n            if (depth[v] == -1) build_component(g,\
    \ v, -1, 0);\n        }\n    }\n\n    int size() const {\n        return n;\n\
    \    }\n\n    bool empty() const {\n        return n == 0;\n    }\n\n    int root()\
    \ const {\n        return roots.empty() ? -1 : roots[0];\n    }\n};\n\n}  // namespace\
    \ tree\n}  // namespace m1une\n\n\n#line 14 \"graph/tree/distance_frequency.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\nnamespace distance_frequency_detail\
    \ {\n\ntemplate <class Mint, class T>\nstd::vector<Mint> count_ordered_pairs(\n\
    \    const m1une::graph::Graph<T>& tree,\n    const CentroidDecomposition<T>&\
    \ decomposition\n) {\n    const int size = tree.size();\n    std::vector<Mint>\
    \ count(static_cast<std::size_t>(size));\n    std::vector<char> removed(std::size_t(size),\
    \ false);\n    std::vector<Mint> histogram;\n    std::vector<std::pair<int, int>>\
    \ stack;\n    std::vector<int> parent(std::size_t(size), -1);\n\n    for (int\
    \ centroid : decomposition.order) {\n        std::vector<Mint> total(1, Mint(1));\n\
    \        for (const auto& edge : tree[centroid]) {\n            if (!edge.alive\
    \ || removed[std::size_t(edge.to)]) continue;\n\n            histogram.clear();\n\
    \            stack.clear();\n            stack.emplace_back(edge.to, 1);\n   \
    \         parent[std::size_t(edge.to)] = centroid;\n            while (!stack.empty())\
    \ {\n                const auto [vertex, distance] = stack.back();\n         \
    \       stack.pop_back();\n                if (int(histogram.size()) <= distance)\
    \ {\n                    histogram.resize(std::size_t(distance + 1));\n      \
    \          }\n                histogram[std::size_t(distance)] += Mint(1);\n\n\
    \                for (const auto& next : tree[vertex]) {\n                   \
    \ if (!next.alive || removed[std::size_t(next.to)]) continue;\n              \
    \      if (next.to == parent[std::size_t(vertex)]) continue;\n               \
    \     parent[std::size_t(next.to)] = vertex;\n                    stack.emplace_back(next.to,\
    \ distance + 1);\n                }\n            }\n\n            if (total.size()\
    \ < histogram.size()) {\n                total.resize(histogram.size());\n   \
    \         }\n            for (std::size_t distance = 0; distance < histogram.size();\
    \ distance++) {\n                total[distance] += histogram[distance];\n   \
    \         }\n\n            const std::vector<Mint> within_component =\n      \
    \          m1une::fps::convolution(histogram, histogram);\n            const std::size_t\
    \ limit = std::min(count.size(), within_component.size());\n            for (std::size_t\
    \ distance = 0; distance < limit; distance++) {\n                count[distance]\
    \ -= within_component[distance];\n            }\n        }\n\n        const std::vector<Mint>\
    \ through_centroid =\n            m1une::fps::convolution(total, total);\n   \
    \     const std::size_t limit = std::min(count.size(), through_centroid.size());\n\
    \        for (std::size_t distance = 0; distance < limit; distance++) {\n    \
    \        count[distance] += through_centroid[distance];\n        }\n        removed[std::size_t(centroid)]\
    \ = true;\n    }\n    return count;\n}\n\ninline std::uint64_t combine_residues(std::uint32_t\
    \ first, std::uint32_t second) {\n    using First = m1une::math::ModInt<998244353>;\n\
    \    using Second = m1une::math::ModInt<924844033>;\n    static const std::uint64_t\
    \ inverse = Second(First::mod()).inv().val();\n    const std::uint64_t offset\
    \ =\n        (std::uint64_t(second) + Second::mod() - first % Second::mod()) %\n\
    \        Second::mod();\n    const std::uint64_t multiplier = offset * inverse\
    \ % Second::mod();\n    return std::uint64_t(first) + std::uint64_t(First::mod())\
    \ * multiplier;\n}\n\n}  // namespace distance_frequency_detail\n\ntemplate <class\
    \ T>\nstd::vector<long long> tree_distance_frequency(\n    const m1une::graph::Graph<T>&\
    \ tree\n) {\n    const int size = tree.size();\n    assert(tree.edge_count() ==\
    \ std::max(0, size - 1));\n    if (size == 0) return {};\n\n    const CentroidDecomposition<T>\
    \ decomposition(tree);\n    assert(decomposition.roots.size() == 1);\n\n    using\
    \ First = m1une::math::ModInt<998244353>;\n    using Second = m1une::math::ModInt<924844033>;\n\
    \    assert(\n        std::uint64_t(size) * std::uint64_t(size - 1) <\n      \
    \  std::uint64_t(First::mod()) * Second::mod()\n    );\n    const std::vector<First>\
    \ first =\n        distance_frequency_detail::count_ordered_pairs<First>(\n  \
    \          tree,\n            decomposition\n        );\n    const std::vector<Second>\
    \ second =\n        distance_frequency_detail::count_ordered_pairs<Second>(\n\
    \            tree,\n            decomposition\n        );\n\n    std::vector<long\
    \ long> result(static_cast<std::size_t>(size));\n    result[0] = size;\n    for\
    \ (int distance = 1; distance < size; distance++) {\n        const std::uint64_t\
    \ ordered =\n            distance_frequency_detail::combine_residues(\n      \
    \          first[std::size_t(distance)].val(),\n                second[std::size_t(distance)].val()\n\
    \            );\n        assert((ordered & 1) == 0);\n        result[std::size_t(distance)]\
    \ = static_cast<long long>(ordered / 2);\n    }\n    return result;\n}\n\n}  //\
    \ namespace tree\n}  // namespace m1une\n\n\n#line 5 \"verify/graph/tree/distance_frequency.test.cpp\"\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\
    \n#include <cerrno>\n#include <charconv>\n#line 8 \"utilities/fast_io.hpp\"\n\
    #include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include\
    \ <iterator>\n#include <string>\n#include <sys/stat.h>\n#line 17 \"utilities/fast_io.hpp\"\
    \n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
    \ {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\n\
    struct is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T,\
    \ std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
    >> : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool is_range_v\
    \ = is_range<T>::value;\n\ntemplate <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c > ' ') {\n            value.push_back(char(c));\n           \
    \ c = read_char_raw();\n        }\n        return true;\n    }\n\n    bool read(bool&\
    \ value) {\n        int x;\n        if (!read(x)) return false;\n        value\
    \ = x != 0;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (_streaming) return read_integer_from_stream(value);\n\
    \        if (!prepare_number()) return false;\n        int c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        while (c <= ' ') c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n\n        bool negative = false;\n        if (c\
    \ == '-') {\n            negative = true;\n            c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        }\n\n        if constexpr (internal::is_signed_v<T>)\
    \ {\n            T result = 0;\n            while ('0' <= c && c <= '9') {\n \
    \               const int first = c - '0';\n                const int second =\
    \ static_cast<unsigned char>(_buffer[_position]) - '0';\n                if (0\
    \ <= second && second <= 9) {\n                    result = negative ? result\
    \ * 100 - (first * 10 + second)\n                                      : result\
    \ * 100 + (first * 10 + second);\n                    ++_position;\n         \
    \       } else {\n                    result = negative ? result * 10 - first\
    \ : result * 10 + first;\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = result;\n \
    \       } else {\n            T result = 0;\n            while ('0' <= c && c\
    \ <= '9') {\n                const unsigned first = unsigned(c - '0');\n     \
    \           const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = result * 100 + T(first * 10 + unsigned(second));\n             \
    \       ++_position;\n                } else {\n                    result = result\
    \ * 10 + T(first);\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = negative ?\
    \ T(0) - result : result;\n        }\n        if (_position > _length) _position\
    \ = _length;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>,\
    \ bool>\n    read(T& value) {\n        if (!skip_spaces()) return false;\n   \
    \     int c = read_char_raw();\n        bool negative = false;\n        if (c\
    \ == '-' || c == '+') {\n            negative = c == '-';\n            c = read_char_raw();\n\
    \        }\n\n        long double result = 0;\n        while ('0' <= c && c <=\
    \ '9') {\n            result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 9 \"verify/graph/tree/distance_frequency.test.cpp\"\
    \n#include <queue>\n#line 11 \"verify/graph/tree/distance_frequency.test.cpp\"\
    \n\nnamespace {\n\nusing Graph = m1une::graph::Graph<int>;\n\nstd::vector<long\
    \ long> naive_distance_frequency(const Graph& tree) {\n    const int size = tree.size();\n\
    \    std::vector<long long> result(static_cast<std::size_t>(size));\n    if (size\
    \ == 0) return result;\n    result[0] = size;\n    for (int source = 0; source\
    \ < size; source++) {\n        std::vector<int> distance(static_cast<std::size_t>(size),\
    \ -1);\n        std::queue<int> queue;\n        distance[static_cast<std::size_t>(source)]\
    \ = 0;\n        queue.push(source);\n        while (!queue.empty()) {\n      \
    \      const int vertex = queue.front();\n            queue.pop();\n         \
    \   for (const auto& edge : tree[vertex]) {\n                if (!edge.alive ||\
    \ distance[static_cast<std::size_t>(edge.to)] != -1) {\n                    continue;\n\
    \                }\n                distance[static_cast<std::size_t>(edge.to)]\
    \ =\n                    distance[static_cast<std::size_t>(vertex)] + 1;\n   \
    \             queue.push(edge.to);\n            }\n        }\n        for (int\
    \ target = source + 1; target < size; target++) {\n            result[static_cast<std::size_t>(\n\
    \                distance[static_cast<std::size_t>(target)]\n            )]++;\n\
    \        }\n    }\n    return result;\n}\n\nvoid test_edge_cases() {\n    Graph\
    \ empty;\n    assert(m1une::tree::tree_distance_frequency(empty).empty());\n\n\
    \    Graph single(1);\n    std::vector<long long> one{1};\n    assert(m1une::tree::tree_distance_frequency(single)\
    \ == one);\n\n    Graph path(100);\n    for (int vertex = 1; vertex < 100; vertex++)\
    \ {\n        path.add_edge(vertex - 1, vertex);\n    }\n    const std::vector<long\
    \ long> path_frequency =\n        m1une::tree::tree_distance_frequency(path);\n\
    \    for (int distance = 0; distance < 100; distance++) {\n        assert(path_frequency[static_cast<std::size_t>(distance)]\
    \ == 100 - distance);\n    }\n\n    Graph star(100);\n    for (int vertex = 1;\
    \ vertex < 100; vertex++) star.add_edge(0, vertex);\n    const std::vector<long\
    \ long> star_frequency =\n        m1une::tree::tree_distance_frequency(star);\n\
    \    assert(star_frequency[0] == 100);\n    assert(star_frequency[1] == 99);\n\
    \    assert(star_frequency[2] == 99LL * 98 / 2);\n    for (int distance = 3; distance\
    \ < 100; distance++) {\n        assert(star_frequency[static_cast<std::size_t>(distance)]\
    \ == 0);\n    }\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 0xa93e72c16b40d5f8ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 500; trial++) {\n        const int size = int(random() % 40) + 1;\n      \
    \  Graph tree(size);\n        for (int vertex = 1; vertex < size; vertex++) {\n\
    \            tree.add_edge(vertex, int(random() % std::uint64_t(vertex)));\n \
    \       }\n        assert(\n            m1une::tree::tree_distance_frequency(tree)\
    \ ==\n            naive_distance_frequency(tree)\n        );\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n   \
    \ m1une::utilities::FastOutput fast_output;\n\n    test_edge_cases();\n    test_randomized();\n\
    \n    int size;\n    fast_input >> size;\n    Graph tree(size);\n    for (int\
    \ edge = 0; edge + 1 < size; edge++) {\n        int first, second;\n        fast_input\
    \ >> first >> second;\n        tree.add_edge(first, second);\n    }\n\n    const\
    \ std::vector<long long> frequency =\n        m1une::tree::tree_distance_frequency(tree);\n\
    \    for (int distance = 1; distance < size; distance++) {\n        if (distance\
    \ != 1) fast_output << ' ';\n        fast_output << frequency[static_cast<std::size_t>(distance)];\n\
    \    }\n    fast_output << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \n\n#include \"../../../graph/graph.hpp\"\n#include \"../../../graph/tree/distance_frequency.hpp\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <queue>\n#include <vector>\n\nnamespace {\n\nusing Graph = m1une::graph::Graph<int>;\n\
    \nstd::vector<long long> naive_distance_frequency(const Graph& tree) {\n    const\
    \ int size = tree.size();\n    std::vector<long long> result(static_cast<std::size_t>(size));\n\
    \    if (size == 0) return result;\n    result[0] = size;\n    for (int source\
    \ = 0; source < size; source++) {\n        std::vector<int> distance(static_cast<std::size_t>(size),\
    \ -1);\n        std::queue<int> queue;\n        distance[static_cast<std::size_t>(source)]\
    \ = 0;\n        queue.push(source);\n        while (!queue.empty()) {\n      \
    \      const int vertex = queue.front();\n            queue.pop();\n         \
    \   for (const auto& edge : tree[vertex]) {\n                if (!edge.alive ||\
    \ distance[static_cast<std::size_t>(edge.to)] != -1) {\n                    continue;\n\
    \                }\n                distance[static_cast<std::size_t>(edge.to)]\
    \ =\n                    distance[static_cast<std::size_t>(vertex)] + 1;\n   \
    \             queue.push(edge.to);\n            }\n        }\n        for (int\
    \ target = source + 1; target < size; target++) {\n            result[static_cast<std::size_t>(\n\
    \                distance[static_cast<std::size_t>(target)]\n            )]++;\n\
    \        }\n    }\n    return result;\n}\n\nvoid test_edge_cases() {\n    Graph\
    \ empty;\n    assert(m1une::tree::tree_distance_frequency(empty).empty());\n\n\
    \    Graph single(1);\n    std::vector<long long> one{1};\n    assert(m1une::tree::tree_distance_frequency(single)\
    \ == one);\n\n    Graph path(100);\n    for (int vertex = 1; vertex < 100; vertex++)\
    \ {\n        path.add_edge(vertex - 1, vertex);\n    }\n    const std::vector<long\
    \ long> path_frequency =\n        m1une::tree::tree_distance_frequency(path);\n\
    \    for (int distance = 0; distance < 100; distance++) {\n        assert(path_frequency[static_cast<std::size_t>(distance)]\
    \ == 100 - distance);\n    }\n\n    Graph star(100);\n    for (int vertex = 1;\
    \ vertex < 100; vertex++) star.add_edge(0, vertex);\n    const std::vector<long\
    \ long> star_frequency =\n        m1une::tree::tree_distance_frequency(star);\n\
    \    assert(star_frequency[0] == 100);\n    assert(star_frequency[1] == 99);\n\
    \    assert(star_frequency[2] == 99LL * 98 / 2);\n    for (int distance = 3; distance\
    \ < 100; distance++) {\n        assert(star_frequency[static_cast<std::size_t>(distance)]\
    \ == 0);\n    }\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 0xa93e72c16b40d5f8ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 500; trial++) {\n        const int size = int(random() % 40) + 1;\n      \
    \  Graph tree(size);\n        for (int vertex = 1; vertex < size; vertex++) {\n\
    \            tree.add_edge(vertex, int(random() % std::uint64_t(vertex)));\n \
    \       }\n        assert(\n            m1une::tree::tree_distance_frequency(tree)\
    \ ==\n            naive_distance_frequency(tree)\n        );\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n   \
    \ m1une::utilities::FastOutput fast_output;\n\n    test_edge_cases();\n    test_randomized();\n\
    \n    int size;\n    fast_input >> size;\n    Graph tree(size);\n    for (int\
    \ edge = 0; edge + 1 < size; edge++) {\n        int first, second;\n        fast_input\
    \ >> first >> second;\n        tree.add_edge(first, second);\n    }\n\n    const\
    \ std::vector<long long> frequency =\n        m1une::tree::tree_distance_frequency(tree);\n\
    \    for (int distance = 1; distance < size; distance++) {\n        if (distance\
    \ != 1) fast_output << ' ';\n        fast_output << frequency[static_cast<std::size_t>(distance)];\n\
    \    }\n    fast_output << '\\n';\n}\n"
  dependsOn:
  - graph/graph.hpp
  - graph/tree/distance_frequency.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/modint.hpp
  - graph/tree/centroid_decomposition.hpp
  - graph/graph.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/tree/distance_frequency.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/tree/distance_frequency.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/tree/distance_frequency.test.cpp
- /verify/verify/graph/tree/distance_frequency.test.cpp.html
title: verify/graph/tree/distance_frequency.test.cpp
---
