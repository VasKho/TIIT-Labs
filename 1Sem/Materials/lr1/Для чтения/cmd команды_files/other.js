window.onload=function(){e=document.getElementsByTagName('div');for(var k=0;k<e.length;k++){if(e[k].className.indexOf('share42init')!=-1){if(e[k].getAttribute('data-url')!=-1)u=e[k].getAttribute('data-url');if(e[k].getAttribute('data-title')!=-1)t=e[k].getAttribute('data-title');if(e[k].getAttribute('data-image')!=-1)i=e[k].getAttribute('data-image');if(e[k].getAttribute('data-description')!=-1)d=e[k].getAttribute('data-description');if(e[k].getAttribute('data-path')!=-1)f=e[k].getAttribute('data-path');if(!f){function path(name){var sc=document.getElementsByTagName('script'),sr=new RegExp('^(.*/|)('+name+')([#?]|$)');for(var i=0,scL=sc.length;i<scL;i++){var m=String(sc[i].src).match(sr);if(m){if(m[1].match(/^((https?|file)\:\/{2,}|\w:[\/\\])/))return m[1];if(m[1].indexOf("/")==0)return m[1];b=document.getElementsByTagName('base');if(b[0]&&b[0].href)return b[0].href+m[1];else return document.location.pathname.match(/(.*[\/\\])/)[0]+m[1];}}return null;}f=path('other.js');}if(!u)u=location.href;if(!t)t=document.title;if(!i)i='data:image/gif;base64,R0lGODlhAQABAIAAAP///wAAACH5BAEAAAAALAAAAAABAAEAAAICRAEAOw==';function desc(){var meta=document.getElementsByTagName('meta');for(var m=0;m<meta.length;m++){if(meta[m].name.toLowerCase()=='description'){return meta[m].content;}}return'';}if(!d)d=desc();u=encodeURIComponent(u);t=encodeURIComponent(t);t=t.replace('\'','%27');i=encodeURIComponent(i);d=encodeURIComponent(d);var s=new Array('"#" data-count="vk" onclick="window.open(\'http://vk.com/share.php?url='+u+'&title='+t+'&image='+i+'&description='+d+'\', \'_blank\', \'scrollbars=0, resizable=1, menubar=0, left=100, top=100, width=550, height=440, toolbar=0, status=0\');return false" title="Поделиться В Контакте"','"#" data-count="fb" onclick="window.open(\'http://www.facebook.com/sharer.php?s=100&p[url]='+u+'&p[title]='+t+'&p[summary]='+d+'&p[images][0]='+i+'\', \'_blank\', \'scrollbars=0, resizable=1, menubar=0, left=100, top=100, width=550, height=440, toolbar=0, status=0\');return false" title="Поделиться в Facebook"','"#" data-count="twi" onclick="window.open(\'https://twitter.com/intent/tweet?text='+t+'&url='+u+'\', \'_blank\', \'scrollbars=0, resizable=1, menubar=0, left=100, top=100, width=550, height=440, toolbar=0, status=0\');return false" title="Добавить в Twitter"','"#" onclick="window.open(\'https://plus.google.com/share?url='+u+'\', \'_blank\', \'scrollbars=0, resizable=1, menubar=0, left=100, top=100, width=550, height=440, toolbar=0, status=0\');return false" title="Поделиться в Google+"','"http://bobrdobr.ru/add.html?url='+u+'&title='+t+'&desc='+d+'" title="Забобрить"','"" onclick="return fav(this);" title="Сохранить в избранное браузера"');var l='';for(j=0;j<s.length;j++)l+='<a rel="nofollow" style="display:inline-block;vertical-align:bottom;width:16px;height:16px;margin:0 6px 6px 0;padding:0;outline:none;background:url('+f+'icons.png) -'+16*j+'px 0 no-repeat" href='+s[j]+' target="_blank"></a>';e[k].innerHTML='<span id="share42">'+l+'</span>';}};};function fav(a){title=document.title;url=document.location;try{window.external.AddFavorite(url,title);}catch(e){try{window.sidebar.addPanel(title,url,"");}catch(e){if(typeof(opera)=="object"){a.rel="sidebar";a.title=title;a.url=url;return true;}else{alert('Нажмите Ctrl-D, чтобы добавить страницу в закладки');}}}return false;};

$(document).ready(function(e) {
if ($("#page").height() > $("#sidebar").height()) {
$("#sidebar").height($("#page").height());
}

$(".nav_menu-2 li").prepend("<span></span>");
$(".sub-menu li span").remove();

$(".nav_menu-2 span").toggle(
function () {

        $(this).addClass("activ").next().next().css({"display":"block"});
      },
function () {
        $(this).removeClass("activ").next().next().css({"display":"none"});
      });

if($(".menu .current-menu-item")){$(".current-menu-item").parent().css({"display":"block"});};
if($(".menu .current-menu-item")){$(".current-menu-item").parent().parent().find("span").addClass("activ");};
if($(".menu .current-menu-item")){$(".current-menu-item").parent().find("span").removeClass("activ");};



}); // the end