import os
# LaTeX 模板头部
latex_template = r"""
\documentclass[UTF8, a4paper, titlepage, twoside]{ctexart}
\usepackage{geometry}
\usepackage{hyperref}
\usepackage{graphicx}
\usepackage{titlesec}
\usepackage{minted}
\usepackage[dvipsnames, svgnames, x11names]{xcolor}
% 设置边距和页面布局
\geometry{left=2.5cm, right=1.5cm, top=1.5cm, bottom=1.5cm, inner=2cm, outer=1cm}
% ------------------------------子章节设置------------------------------
\setcounter{secnumdepth}{4}
\setcounter{tocdepth}{4}
\AtBeginDocument{
	\setlength{\abovedisplayskip}{0.2em}
	\setlength{\belowdisplayskip}{0.2em}
	\setlength{\parskip}{0.5em}
}
\title{	
	\normalfont\normalsize
	\textsc{Beijing Normal University}\\ 
	\vspace{25pt} 
	\rule{\linewidth}{0.5pt}\\ 
	\vspace{20pt} 
	{\Huge Template}\\ 
	\vspace{12pt} 
	\rule{\linewidth}{2pt}\\ 
	\vspace{12pt} 
}
\author{Pray Never} 
\date{\normalsize\today} 
\begin{document}
\maketitle
\tableofcontents
\newpage
"""

# LaTeX 模板尾部
latex_end = r"""
\end{document}
"""

# 遍历目录，按文件夹分组读取 C++ 文件
def gather_cpp_by_folder(directory):
    folder_structure = {}
    for root, _, files in os.walk(directory):
        cpp_files = [file for file in files if file.endswith(".cpp") or file.endswith(".h")]
        if cpp_files:
            folder_name = os.path.basename(root)
            folder_structure[folder_name] = [os.path.join(root, file) for file in cpp_files]
    return folder_structure

# 将文件夹和 C++ 文件嵌入到 LaTeX 文档
def write_latex_with_structure(folder_structure, output_file):
    with open(output_file, 'w', encoding='utf-8') as tex_file:
        tex_file.write(latex_template)  # 写入模板头部
        for folder_name, cpp_files in folder_structure.items():
            tex_file.write(f"\\section{{{folder_name}}}\n")  # 文件夹名作为 \section
            for cpp_file in cpp_files:
                file_name = os.path.basename(cpp_file)  # 文件名作为 \subsection
                tex_file.write(f"\\subsection{{{file_name}}}\n")
                tex_file.write(f"\\begin{{minted}}[frame=lines, fontsize=\\small, linenos]{{C++}}\n")
                with open(cpp_file, 'r', encoding='utf-8') as f:
                    tex_file.write(f.read())  # 写入 C++ 文件内容
                tex_file.write("\n\\end{minted}\n\n")
            tex_file.write("\\clearpage\n")  # 在每个文件夹结束后换页
        tex_file.write(latex_end)  # 写入模板尾部

# 主函数
if __name__ == "__main__":
    cpp_directory = "./"  # 指定 C++ 文件所在目录
    output_tex_file = "template.tex"  # 输出的 LaTeX 文件名

    # 获取按文件夹分组的 C++ 文件结构
    folder_structure = gather_cpp_by_folder(cpp_directory)

    # 生成 LaTeX 文件
    if folder_structure:
        write_latex_with_structure(folder_structure, output_tex_file)
        print(f"LaTeX 文件已生成: {output_tex_file}")
    else:
        print("未找到任何 C++ 文件！")
