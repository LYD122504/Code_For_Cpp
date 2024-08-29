(TeX-add-style-hook
 "TEST"
 (lambda ()
   (setq TeX-command-extra-options
         "-file-line-error -shell-escape")
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("ctexart" "UTF8")))
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "href")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "ctexart"
    "ctexart10"
    "hyperref"
    "amssymb"
    "amsmath"
    "amsthm")
   (LaTeX-add-amsthm-newtheorems
    "theorem"
    "lemma"))
 :latex)

