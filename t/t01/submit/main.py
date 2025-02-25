from latextool_basic import *
p = Plot()
i = 4
def rect(s):
    global i
    i = i + 1
    i = i % 5
    if i == 0 : return Rect(x0=0, y0=0, x1=1, y1=0.6, label=s)
    if i == 1 : return Rect(x0=0, y0=0, x1=1, y1=0.6, label=s)
    elif i == 2: return Rect(x0=0, y0=0, x1=1.4, y1=0.6, label=s)
    elif i == 3: return Rect(x0=0, y0=0, x1=12, y1=0.6, label=s)
    elif i == 4: return Rect(x0=0, y0=0, x1=1.2, y1=0.6, label=s)

m00 = [[r'\texttt{sid}', r'\texttt{eid}', r'\texttt{state}', r'\texttt{note}', r'\texttt{time}'],
]

m10 = [[r'\texttt{%s}' % x for x in ['3',97, '0', 'hi, where\'s the on/off button? thanks. luke', '5']],
       [r'\texttt{%s}' % x for x in ['3',97,'9', 'Luke: It\'s the red button. Chewie.', '10']],
       [r'\texttt{%s}' % x for x in ['3',97,'0', 'where\'s the red button?', '24']],
       [r'\texttt{%s}' % x for x in ['3',97,'9', 'Luke: Open the safety cap. Chewie.', '30']],
       [r'\texttt{%s}' % x for x in ['3',97,'0', 'i do not see a safety cap. luke.', '45']],
       [r'\texttt{%s}' % x for x in ['3',97,'1', 'Check with Yoda. Left msg. Chewie.', '47']],
       [r'\texttt{%s}' % x for x in ['3',97,'4', 'Yoda sent query to Boba. Chewie.', '50']],
       [r'\texttt{%s}' % x for x in ['3',97,'7', 'Boba said it\'s now voice-activated. Chewie.', '65']],
       [r'\texttt{%s}' % x for x in ['3',97,'9', 'Luke: It\'s voice-activated. Chewie.', '68']],
]

M = [[m00],
     [m10]]

N = table3(p, M, rect=rect)
x,y = N[0][0].topleft(); x = x + 0.5; y = y + 0.4
from latexcircuit import *
p += Rect(x0=x, y0=y, x1=x, y1=y, linewidth=0, label=r'\texttt{Notes}')
print(p)

